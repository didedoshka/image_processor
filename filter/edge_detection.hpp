#include "filter.hpp"
#include "apply_matrix.hpp"
#include "change_pixels.hpp"

// здесь у меня проблема, кажется, с архитектурой. мне очень нравится как получается наследование sharpening и negative, grayscale, здесь хотелось бы что-нибудь такое же, но не понимаю что
// из-за этого мне никак не реализовать этот фильтр, не переписав apply_matrix и change_pixels
// в идеале я вызываю grayscale, потом apply_matrix с матрицей из определения и потом change_pixels с функцией, которая перекрашивает в то как надо в зависимости от трешхолд
// можете подсказать, что делать, пожалуйста

class EdgeDetection : public virtual Filter {

};
