#include "Image.hpp"
using namespace std;

int main() {
    int choice;
    cout << "Avalible Filters :" << endl;
    cout << " 1 -> Convolve" << endl;
    cout << " 2 ->  imageThresholding" << endl;
    cout << "Choice "; cin >> choice;
    Image img(choice);
    img.loadImage("pic.png");
    img.applyFilter();
    return 0;
}
