
add_reference(maoni-ref.xml
  ../include/Maoni/Color.hpp
  ../include/Maoni/Enum.hpp
  ../include/Maoni/Math.hpp
  ../include/Maoni/MeshLoader.hpp
  ../include/Maoni/Model.hpp
  ../include/Maoni/RenderAlgorithm.hpp
  ../include/Maoni/ScopedLocks.hpp
  ../include/Maoni/ShaderProgram.hpp
  ../include/Maoni/Teaset.h
  ../include/Maoni/Texture.hpp
  ../include/Maoni/Vector.hpp
  ../include/Maoni/Vertex.hpp
  HEADER_PREFIX Maoni
  )

add_documentation(
  libMaoni.qbk
  maoni-ref.xml
  )
