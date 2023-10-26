add_catch(
    test_image_processor
    pixel.cpp
    image.cpp
    test.cpp
)


add_executable(
    image_processor
    pixel.cpp
    image.cpp
    image_processor.cpp
)
