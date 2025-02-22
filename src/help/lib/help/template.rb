class Template
  def render(temp)
    compress(ERB.new(temp).result(binding))
  rescue SyntaxError => e
    throw StandardError.new(e)
  end

  def compress(html)
    HtmlCompressor::Compressor.new.compress(html)
  end

  def self.path
    raise 'path not defined'
  end

  def output_path
    name = self.class.name.gsub(/\ABlitz3D::Help::/, '').underscore
    File.join(root_path, "#{name}.html")
  end

  def root_path
    File.expand_path('../../../../../_release/help', __dir__)
  end

  def generate(path)
    template = File.read(self.class.path)
    out = render(template) { source }

    File.open(path, 'w') { |f| f.write out }
  end

  def relative_to_root
    relative_to(root_path)
  end

  def relative_to(path)
    output_parts = output_path.split('/')
    path_parts = path.split('/')
    while output_parts.first == path_parts.first && !output_parts.empty? && !path_parts.empty?
      output_parts.shift
      path_parts.shift
    end
    path = [Array.new(output_parts.size - 1) { '..' }, path_parts].flatten.join('/')
    path.present? ? path : '.'
  end
end
