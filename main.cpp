#include "Image.hpp"
using namespace std;

int main() {
    int choice;
    cout << "Avalible Filters :" << endl;
    cout << " 1 -> Sharpen" << endl;
    cout << "2 ->edge Detection" << endl;
    cout << "3 ->Gaussian Blur" << endl;
    cout << "4 ->  imageThresholding" << endl;
    cout << "Choice "; cin >> choice;
    Image img(choice);
    img.loadImage("pic.png");
    img.applyFilter();
    return 0;
}
