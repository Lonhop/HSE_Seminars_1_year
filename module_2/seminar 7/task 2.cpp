#include<iostream>
#include<vector>

class Image {
    int width;
    int height;
    std::vector<int> pixels;
public:
    class Filter {
        int intensity;
    public:
        Filter(int i) : intensity(i) {}
        int apply(int pixel) const {
            int result = pixel + this->intensity * 10;
            return result;
        }
    };
    Image(int w, int h, int value) : width(w), height(h), pixels(w*h, value) {}
    Image(int w,int h) : Image(w,h,0) {}
    Image& applyBrightness(int delta) {
        for (int i = 0; i < pixels.size(); i++) {
            int value = pixels[i] + delta;
            pixels[i] = value;

        }
        return *this;
    }
    Image& applyFilter(const Filter& f) {
        for (int i = 0; i < pixels.size(); i++) {
            pixels[i] = f.apply(pixels[i]);
        }
        return *this;
    }
    void fill(int x,int y,int value) {
        pixels[y * width + x] = value;
    }
    void show() const {
        std::cout << "Image" << width << 'x' << height << ":\n";
        for (int y = 0; y < height; y++) {
            for (int x = 0; x < width; x++) {
                int pixel = pixels[y * width + x];
                std::cout << pixel << '\t';
            }
            std::cout << '\n';
        }
        std::cout <<'\n';
    }
};

int main() {
    Image image(4,4);
    for (int y = 0; y < 4; y++) {
        for (int x = 0; x < 4; x++) {
            image.fill(x,y,(x+y) * 20);
        }
    }
    image.show();
    image.applyBrightness(10)
        .applyFilter(Image::Filter(3))
        .applyBrightness(-5);
    image.show();
    return 0;
}