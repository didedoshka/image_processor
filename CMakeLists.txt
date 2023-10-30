add_catch(
    test_image_processor
    pixel.cpp
    image.cpp
    BMP.cpp
    test.cpp
)


add_executable(
    image_processor
    pixel.cpp
    image.cpp
    BMP.cpp
    image_processor.cpp
    filter/crop.cpp
    filter/change_pixels.cpp
    filter/grayscale.cpp
    filter/negative.cpp
    filter/apply_matrix.cpp
    filter/sharpening.cpp
    filter/gaussian_blur.cpp
    filter/edge_detection.cpp
)
