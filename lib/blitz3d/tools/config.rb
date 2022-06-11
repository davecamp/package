require 'pathname'

module Blitz3D
  module Tools
    module Config
      TOOLCHAINS_DIR = File.join(File.dirname(Blitz3D.path), '..', '_release', 'toolchains')

      def file_has_changed?(file, string)
        File.open(file).read != string
      rescue Errno::ENOENT
        true
      end

      def link_stub(mod)
        puts "Generating stub for #{mod.name.bold}..."
        f = StringIO.new
        f.write "// AUTOGENERATED. DO NOT EDIT.\n"
        f.write "// RUN `bin/blitz3d config` TO UPDATE.\n\n"
        f.write "#include <bb/blitz/module.h>\n"
        f.write "#include <bb/#{mod.id}/#{mod.id}.h>\n\n"
        f.write "#ifdef WIN32\n"
        f.write "BBMODULE_LINK( #{mod.id.parameterize.underscore} ){\n"
        mod.symbols.each_pair do |ident, sym|
          f.write "\trtSym( \"#{ident}\",#{sym} );\n"
        end

        mod.commands.each do |command|
          params = command.params.map(&:to_rtsym)
          sym = "#{command.return_type}#{command.name}#{params.join('')}".inspect
          f.write "\trtSym( #{sym},#{command.symbol} );\n"
        end
        f.write "}\n"
        f.write "#endif\n"

        out_file = File.join('src', 'modules', 'bb', mod.id, 'module.link.cpp')

        if file_has_changed?(out_file, f.string)
          File.open(out_file, 'w') { |h| h.write f.string }
        end
      end

      def modules
        Module.all.each do |mod|
          if mod.needs_to_link?
            link_stub mod
          else
            FileUtils.rm "src/modules/bb/#{mod.id}/module.link.cpp" rescue Errno::ENOENT
          end
        end
      end

      def runtimes
        Runtime.all.each do |runtime|
          puts "Generating runtime #{runtime.name.bold}..."
          runtime.platforms.each do |platform|
            puts "  #{platform}..."
            modules = runtime.dependencies(:list, platform)

            config = {}
            config[:modules] = modules.map do |mod|
              {
                id: mod.id
              }
            end

            config[:commands] = modules.map do |mod|
              mod.commands.map do |command|
                {
                  name: command.name,
                  return_type: command.return_type,
                  symbol: command.symbol,
                  parameters: command.params.map do |param|
                    { ident: param.identifier, type: param.type, default: param.default }
                  end
                }
              end
            end.flatten

            FileUtils.mkdir_p File.join(TOOLCHAINS_DIR, platform)

            File.open(File.join(TOOLCHAINS_DIR, platform, "#{runtime.id}.runtime.json"), 'w') { |t| t.write JSON.pretty_generate(config) }

            f = StringIO.new
            f.write "// AUTOGENERATED. DO NOT EDIT.\n"
            f.write "// RUN `bin/blitz3d config` TO UPDATE.\n"
            f.write("\n#include <bb/stub/stub.h>\n\n")
            f.write("\n#include \"../../stdutil/stdutil.h\"\n\n")

            modules.each do |mod|
              f.write("BBMODULE_DECL( #{mod.id.parameterize.underscore} );\n")
            end

            f.write("\nclass BBRuntime;\n")
            f.write("BBRuntime *#{runtime.entry['runtime']}();\n")
            f.write("BBRuntime *bbCreateRuntime(){\n")
            f.write("\treturn #{runtime.entry['runtime']}();\n")
            f.write("}\n\n")

            f.write("#ifdef WIN32")
            f.write("\nvoid bbruntime_link( void (*link)( const char *sym,void *pc ) ){\n")
              modules.select(&:needs_to_link?).each do |mod|
                f.write("\t#{mod.id.parameterize.underscore}_link( link );\n")
              end
            f.write("}\n")
            f.write("#endif")

            f.write("\nbool bbruntime_create(){\n")
            write_create_calls = lambda do |i, l|
              (i + 1).times { f.write "\t" }
              id = modules[i].id.parameterize.underscore
              f.write("if( #{id}_create() ){\n")
              (i + 2).times { f.write "\t" }
              if i < modules.size - 1
                l.call(i + 1, l)
                (i + 1).times { f.write "\t" }
                f.write("\t#{id}_destroy();\n");
              else
                (i + 1).times { f.write "\t" }
                f.write("\treturn true;\n")
              end
              (i + 1).times { f.write "\t" }
              f.write("}else sue( \"#{id}_create failed\" );\n")
            end
            write_create_calls.call 0, write_create_calls
            f.write("\treturn false;\n")
            f.write("}\n")

            f.write("\nbool bbruntime_destroy(){\n")
            modules.reverse.each do |mod|
              f.write("\t#{mod.id.parameterize.underscore}_destroy();\n")
            end
            f.write("\treturn true;\n")
            f.write("}\n")

            runtime_stub_file = "src/runtime/#{runtime.id}/#{platform}.cpp"

            if file_has_changed?(runtime_stub_file, f.string)
              File.open(runtime_stub_file, 'w') { |t| t.write f.string }
            end
          end

          f = StringIO.new
          f.write "# AUTOGENERATED. DO NOT EDIT.\n"
          f.write "# RUN `bin/blitz3d config` TO UPDATE.\n\n"
          f.write "include_directories (SYSTEM ../../modules)\n\n"

          f.write "set(SOURCES false)\n\n"

          runtime.platforms.each.with_index do |platform, i|
            f.write("#{'ELSE' if i > 0}IF(BB_#{platform.upcase})\n")
            f.write("  set(SOURCES #{platform}.cpp)\n")
            f.write("ENDIF()\n\n") if i == runtime.platforms.size - 1
          end

          f.write "if(NOT SOURCES)\n"
          f.write "  return()\n"
          f.write "endif()\n"

          f.write "\nset(DEPENDS_ON )\n\n"

          runtime.dependencies(:list).each do |dep|
            f.write("bb_addmodule(bb.#{dep.id})\n")
          end

          f.write "\n"

          f.write "bb_runtime(#{runtime.id})\n"

          out_file = "src/runtime/#{runtime.id}/CMakeLists.txt"
          if file_has_changed?(out_file, f.string)
            File.open(out_file, 'w') { |t| t.write f.string }
          end
        end
      end

      def run
        modules
        runtimes
      end
    end
  end
end
