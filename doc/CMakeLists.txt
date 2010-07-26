
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

add_documentation(libMaoni.qbk
    motivation.qbk
    getstarted.qbk
    tutorial.qbk
    examples.qbk
    maoni-ref.xml
    design.qbk
    software.qbk
  IMAGES
    ../src/Images/Splashscreen.jpg
    images/parallel_dragon.jpg
    images/dragon_blinnphong.jpg
    images/dragon_comicstyle.jpg
    images/rockerarm_fixedfunction.jpg
    images/dragon_spheremapping.jpg
    images/dgl_bump_mapping.jpg
    images/ozone_bump_mapping.jpg
    images/swiftless_bump_mapping.jpg
  )
