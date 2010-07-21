
add_reference(maoni-ref.xml
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
  HEADER_PREFIX Maoni
  )

add_documentation(
  libMaoni.qbk
  motivation.qbk
  getstarted.qbk
  tutorial.qbk
  examples.qbk
  maoni-ref.xml
  design.qbk
  software.qbk
  parallel_dragon.jpg
  dragon_blinnphong.jpg
  dragon_comicstyle.jpg
  rockerarm_fixedfunction.jpg
  dragon_spheremapping.jpg
  dgl_bump_mapping.jpg
  ozone_bump_mapping.jpg
  swiftless_bump_mapping.jpg
  )
