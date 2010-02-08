
doxygen_to_boostbook(maoni-ref.xml
  ../include/Maoni/Color.hpp
  ../include/Maoni/Enum.hpp
  ../include/Maoni/MeshLoader.hpp
  ../include/Maoni/Model.hpp
  ../include/Maoni/RenderAlgorithm.hpp
  ../include/Maoni/ScopedLocks.hpp
  ../include/Maoni/ShaderProgram.hpp
  ../include/Maoni/Texture.hpp
  ../include/Maoni/Vector.hpp
  ../include/Maoni/Vertex.hpp
  )

quickbook_to_boostbook(maoni-doc.xml
  libMaoni.qbk maoni-ref.xml
  )
