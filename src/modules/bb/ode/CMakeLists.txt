# TODO: figure out why it won't compile on android/ios.
if(TARGET ODE)
  bb_start_module(ode)
  set(DEPENDS_ON bb.blitz3d)
  set(SOURCES commands.h ode.h ode.cpp world.cpp space.cpp joints.cpp collision.cpp geom.cpp trimesh.cpp body.cpp jv-ode-compat.cpp)
  set(LIBS ODE)
  bb_end_module()
endif()
