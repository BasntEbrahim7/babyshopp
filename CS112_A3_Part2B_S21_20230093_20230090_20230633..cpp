// File: CS112_A3_Part2B_S21_20230093_20230090_20230633.

// Emails: basmala.ashrafabdelrahim2005@gmail.com - basntebrahim5@gmail.com - bosbosa2005@gmail.com

// ID1: 20230093 – do filters (2, 5, 8, 11,16)

// ID2: 20230090 - do filters(1, 4, 7, 10,13)

// ID3: 20230633 - do filters( 3, 6, 9, 12,17)

// explain: this program take image filename from user and show a complete menu to choose which filter does he nead to apply

#include "Image_Class.h"
#include <iostream>
#include <fstream>
#include <algorithm> // for std::min and std::max
#include <limits>    // for numeric_limits
#include <cmath> // For sqrt function
#include <string>


using namespace std;
// Function declarations
void save_image(Image& image,const string& filename);
int load_new_image();

void Gray_scale_filter(Image& image, const string& filename);
void Black_White_Filter(Image& image, const string& filename);
void invert_color_filter(Image& image, const string& filename);
int  Merge_images(Image& image, const string& filename);
void flip_filter(Image& image, const string& filename);
void Rotate_image(Image& image, const string& filename);
void dark_light_filter(Image& image, const string& filename);
void crop_image(Image& image, const string& filename);
int _frame(Image& image, const string& filename);
int detect_edges(Image& image, const string& filename);
void resizing_image(Image& image, const string& filename);
void blur_filter(Image& image, const string& filename);
int sun_light_filter(Image& image, const string& filename);
void purple_filter(Image& image, const string& filename);
void infrared_photography(Image& image, const string& filename);
int main() {
    //load image for editing
    string filename;
    cout << "Enter your file name: ";
    cin >> filename;
    // Check if the file exists
    ifstream file(filename);
    if (!file) {
        cout << "Error: please enter an existing filename image: " << endl;
        main();
        return 1; // Return 1 to indicate an error
    }
    file.close();
    if (filename.find(".jpg") == string::npos && filename.find(".bmp") == string::npos && filename.find(".png")==string::npos) {
        cout << "Error: Only JPG and PNG files are supported." << endl;
        return 1;
    }


    Image image(filename);


    int choice;
start:
    do {


        cout << "\nMenu:\n";
        cout << "16. Load a new image\n";
        cout << " \nChoose a filter to apply:\n";
        cout << "1. Gray scale filter\n";
        cout << "2. Black and White filter\n";
        cout << "3. Invert color filter\n";
        cout << "4.merge images filter \n";
        cout << "5. flip image filter\n";
        cout << "6. rotate image filter\n";
        cout << "7. Darken and Lighten Image filter\n";
        cout << "8. Crop Images filter\n";
        cout << "9. adding frame filter\n";
        cout << "10. Detect Image Edges filter\n";
        cout << "11. Resizing Images filter\n";
        cout << "12. Blur_Images_filter\n";
        cout << "13.sun_light_filter\n ";
        cout <<  "14. purple_filter\n";
        cout << "15.infrared_photography_filter\n ";
        cout<< "17. save the image\n";
        cout<< "18. exit\n";



        cout << "Enter your choice: ";
        cin>>choice;

        switch (choice) {
            case 1:
                 Gray_scale_filter( image, filename);
                break;
            case 2:
                Black_White_Filter(image, filename);
                break;
            case 3:
                invert_color_filter(image, filename);
                break;
            case 4:
                 Merge_images(image, filename);
                break;
            case 5:
                 flip_filter( image,filename);
                break;
            case 6:
                 Rotate_image( image,  filename);
                 break;
            case 7:
                dark_light_filter( image,filename);
                break;
            case 8:
                 crop_image( image, filename);
                 break;
            case 9:
                 _frame( image, filename);
                 break;
            case 10:
                 detect_edges( image, filename);

                 break;
            case 11:
                resizing_image( image,filename);
                break;
            case 12:
                blur_filter( image, filename);
                break;
            case 13:
                sun_light_filter(image, filename);
                break;
            case 14:
                purple_filter(image,filename);
                break;
            case 15:
                 infrared_photography( image,  filename);
                 break;

            case 16:
                // Ask user if they want to save the current image before loading a new one
                char choice;
                cout << "Do you want to save the current image before loading the new one? (y/n): "<<endl;
                cin >> choice;

                if (tolower(choice) == 'y') {
                    save_image( image ,filename);

                }else if(tolower(choice) == 'n'){
                    //continue without saving;

                }

                if (load_new_image()) {
                    goto start;
                } else {
                    return 1; // Return 1 to indicate an error
                }

            case 17:
                 save_image( image ,filename);
                break;
            case 18:
                cout << "Exiting the program.\n";
                break;

            default:
                cout << "Invalid choice. Please enter a number between 1 and 18." << endl;
                // Clear input buffer
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                break;
        }


    } while (choice != 18);

    return 0;

}


int load_new_image() {
    string newFilename;
    cout << "Enter filename of the new image: ";
    cin >> newFilename;


    // Check if the new file exists
    ifstream file(newFilename);
    if (!file) {
        cout << "Error: please enter an existing filename image: " << endl;
        main();
        return 1; // Return 1 to indicate an error
    }
    file.close();
    if (newFilename.find(".jpg") == string::npos && newFilename.find(".png") == string::npos) {
        cout << "Error: Only JPG and PNG files are supported." << endl;
        return 1;
    }



    // Load the new image
    Image image(newFilename);


    cout << "New image loaded successfully.\n";

}
void save_image(Image& image, const string& filename) {
    string saveOption;
    cout << "Do you want to save in the same file or a new file? (same/new): ";
    cin >> saveOption;

    if (saveOption == "same") {
        int returnCode = image.saveImage(filename);
        if (returnCode == 1) {
            cout << "Image saved successfully as " << filename << endl;
        } else {
            cout << "Failed to save the image.\n";
        }
    } else if (saveOption == "new") {
        string saveFilename;
        cout << "Enter filename to save the current image: ";
        cin >> saveFilename;
        int returnCode = image.saveImage(saveFilename);
        if (returnCode == 1) {
            cout << "Image saved successfully as " << saveFilename << endl;
        } else {
            cout << "Failed to save the image.\n";
        }
    } else {
        cout << "Invalid option. Please enter 'same' or 'new'.\n";
    }
}
// Implementations of filter functions
void dark_light_filter(Image& image, const string& filename) {
    int choice;
    cout << "Choose:\n";
    cout << "1. Dark filter\n";
    cout << "2. Light filter\n";
    cin >> choice;

    if (choice == 1) {
        // Darken Image
        for (int i = 0; i < image.width; ++i) {
            for (int j = 0; j < image.height; ++j) {
                for (int k = 0; k < image.channels; ++k) {
                    // Reduce pixel value by 50%
                    image(i, j, k) = image(i, j, k) / 2;
                }
            }
        }

    } else if (choice == 2) {
        // Lighten Image
        for (int i = 0; i < image.width; ++i) {
            for (int j = 0; j < image.height; ++j) {
                for (int k = 0; k < image.channels; ++k) {
                    // Increase pixel value by 50%, clamping to the range [0, 255]
                    int new_value = static_cast<int>(image(i, j, k)) * 3 / 2;
                    image(i, j, k) = static_cast<unsigned char>(std::min(std::max(0, new_value), 255));
                }
            }
        }

    } else {
        cout << "Invalid choice. Please choose 1 for Darken Image or 2 for Lighten Image." << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        return dark_light_filter(image,filename);

    }
}

void flip_filter(Image& image, const string& filename) {
    int choice;
    cout << "Choose flip direction:\n";
    cout << "1. Vertical flip\n";
    cout << "2. Horizontal flip\n";
    cin >> choice;

    if (choice == 1) {
        // Vertical flip
        for (int i = 0; i < image.width; ++i) {
            for (int j = 0; j < image.height / 2; ++j) { // Only iterate up to half the height for vertical flip
                for (int k = 0; k < image.channels; ++k) {
                    // Swap pixels vertically to flip the image
                    std::swap(image(i, j, k), image(i, image.height - 1 - j, k));
                }
            }
        }

    } else if (choice == 2) {
        // Horizontal flip
        for (int i = 0; i < image.width / 2; ++i) { // Only iterate up to half the width for horizontal flip
            for (int j = 0; j < image.height; ++j) {
                for (int k = 0; k < image.channels; ++k) {
                    // Swap pixels horizontally to flip the image
                    std::swap(image(i, j, k), image(image.width - 1 - i, j, k));
                }
            }
        }

    } else {
        cout << "Invalid choice. Please choose 1 for vertical flip or 2 for horizontal flip." << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return flip_filter(image,filename);
    }
}

void invert_color_filter(Image& image, const string& filename) {
    for (int i = 0; i < image.width; ++i) {
        for (int j = 0; j < image.height; ++j) {
            for (int k = 0; k < image.channels; ++k) {
                // Invert color by subtracting from 255
                image(i, j, k) = 255 - image(i, j, k);
            }
        }
    }

}

void Gray_scale_filter(Image& image, const string& filename) {
    for (int i = 0; i < image.width; ++i) {
        for (int j = 0; j < image.height; ++j) {
            unsigned int avg = 0;
            for (int k = 0; k < image.channels; ++k) {
                avg += image(i, j, k);
            }
            avg /= 3;
            image(i, j, 0) = avg;
            image(i, j, 1) = avg;
            image(i, j, 2) = avg;
        }
    }

}

void Black_White_Filter(Image& image, const string& filename) {
    for (int i = 0; i < image.width; ++i) {
        for (int j = 0; j < image.height; ++j) {
            unsigned int avg = 0;
            for (int k = 0; k < image.channels; ++k) {
                avg += image(i, j, k);
            }
            avg /= 3;
            unsigned int threshold = 128; // You can adjust this threshold as needed
            unsigned int newValue = (avg < threshold) ? 0 : 255;
            for (int k = 0; k < 3; ++k) {
                image(i, j, k) = newValue;
            }
        }
    }

}
int  Merge_images(Image& image, const string& filename) {


        try {
            // Prompt the user to enter filenames for the two images
            string firstImageFilename, secondImageFilename;
             firstImageFilename=filename;

            cout << "Enter the filename of the second image: ";
            cin >> secondImageFilename;


            // Load the two images
            Image firstImage(firstImageFilename);
            Image secondImage(secondImageFilename);


            // Create a new image with the dimensions of the first image
            Image mergedImage(firstImage.width, firstImage.height);

            // Calculate the scaling factors for the second image
            float scaleX = (float)firstImage.width / secondImage.width;
            float scaleY = (float)firstImage.height / secondImage.height;

            // Merge the images
            for (int x = 0; x < firstImage.width; ++x) {
                for (int y = 0; y < firstImage.height; ++y) {
                    for (int channel = 0; channel < 3; ++channel) {
                        // Calculate the corresponding coordinates in the second image
                        int srcX = min((int)(x / scaleX), secondImage.width - 1);
                        int srcY = min((int)(y / scaleY), secondImage.height - 1);

                        // Get pixel values from both images and merge
                        pixel pixelFromFirstImage = firstImage(x, y, channel);
                        pixel pixelFromSecondImage = secondImage(srcX, srcY, channel);
                        mergedImage(x, y, channel) = (pixelFromFirstImage + pixelFromSecondImage) / 2;
                    }
                }
            }

            string newFilename;
        char choice;
        cout << "Do you want to save the merged image with a new name? (Y/N): ";
        cin >> choice;
    // Check if the choice is valid
        while (choice != 'Y' && choice != 'y' && choice != 'N' && choice != 'n') {
                cout << "Please enter a valid choice (Y/N): ";
            cin >> choice;
            }

    if (choice == 'Y' || choice == 'y') {
        cout << "Enter new file name: ";
        cin >> newFilename;
        mergedImage.saveImage(newFilename); // Save with new file name
    } else {
        mergedImage.saveImage(filename); // Save with the same name
    }

    cout << "Image merged and saved successfully!" << endl;

        } catch (const exception& ex) {
            cerr << "Error: " << ex.what() << endl;
            return 1;
        } catch (...) {
            cerr << "Unknown error occurred." << endl;
            return 1;
        }

        return 0;
    }

void Rotate_image(Image& image, const string& filename){


    Image image2(image.height, image.width);
    Image image3(image.width,image.height);
    int choice ;
    cout<< "enter the number of rotate 90/180/270/360 : ";
    cin>>choice;
    if(choice == 180){
        for (int i = 0; i < image.width; i++) {
            for (int j = 0; j < image.height; j++) {
                for (int k = 0; k < image.channels; k++) {
                    image3(i, j, k) = image(image.width - 1 - i, image.height - 1 - j, k);
                }
            }
        }
        image=image3;
        image.saveImage(filename);
    }
    else if(choice == 270) {
        for (int i = 0; i < image.width; i++) {
            for (int j = 0; j < image.height; j++) {
                for (int k = 0; k < image.channels; k++) {
                    image2(j, image.width - 1 - i, k) = image(i, j, k);

                }
            }
        }
        image=image2;

        image.saveImage(filename);

    }
    else if(choice == 90){
        Image image2(image.height, image.width);
        for (int i = 0; i < image.width; i++) {
            for (int j = 0; j < image.height; j++) {
                for (int k = 0; k < image.channels; k++) {
                    image2(image.height -1 -j, i, k) = image(i, j, k);

                }
            }
        }
        image=image2;
        image.saveImage(filename);
    }
    else if (choice == 360){
       image.saveImage(filename);
    }
    else{
        cout<<"Invalid number try again !";
    }

}

void crop_image(Image& image, const string& filename){
    int x, y, cropWidth, cropHeight;
    while (true) {
        cout << "Enter x coordinate for starting point: ";
        if (!(cin >> x)) {
            cout << "Invalid input. Please enter a valid integer." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            // Check if crop dimensions are within the image bounds
        } else if (x < 0 || x >= image.width) {
            cout << "Invalid input. Please enter a valid integer within image bounds." << endl;
        } else {
            break;
        }
    }

    while (true) {
        cout << "Enter y coordinate for starting point: ";
        if (!(cin >> y)) {
            cout << "Invalid input. Please enter a valid integer." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            // Check if crop dimensions are within the image bounds

        } else if (y < 0 || y >= image.height) {
            cout << "Invalid input. Please enter a valid integer within image bounds." << endl;
        } else {
            break;
        }
    }

    while (true) {
        cout << "Enter width for cropping: ";
        if (!(cin >> cropWidth)) {
            cout << "Invalid input. Please enter a valid integer." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            // Check if crop dimensions are within the image bounds
        } else if (cropWidth <= 0 || x + cropWidth > image.width) {
            cout << "Invalid input. Please enter a valid positive integer within image bounds." << endl;
        } else {
            break;
        }
    }

    while (true) {
        cout << "Enter height for cropping: ";
        if (!(cin >> cropHeight)) {
            cout << "Invalid input. Please enter a valid integer." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            // Check if crop dimensions are within the image bounds
        } else if (cropHeight <= 0 || y + cropHeight > image.height) {
            cout << "Invalid input. Please enter a valid positive integer within image bounds." << endl;
        } else {
            break;
        }
    }

    Image croppedImage(cropWidth, cropHeight);

    for (int i = 0; i < cropWidth; ++i) {
        for (int j = 0; j < cropHeight; ++j) {
            for (int k = 0; k < image.channels; ++k) {
                croppedImage(i, j, k) = image(x + i, y + j, k); // Crop the image
            }
        }
    }
    string newFilename;
    char choice;
    cout << "Do you want to save the cropped image with a new name? (Y/N): ";
    cin >> choice;
    // Check if the choice is valid
    while (choice != 'Y' && choice != 'y' && choice != 'N' && choice != 'n') {
        cout << "Please enter a valid choice (Y/N): ";
        cin >> choice;
    }

    if (choice == 'Y' || choice == 'y') {
        cout << "Enter new file name: ";
        cin >> newFilename;
        croppedImage.saveImage(newFilename); // Save with new file name
    } else {
        croppedImage.saveImage(filename); // Save with the same name
    }

    cout << "Image cropped and saved successfully!" << endl;

}

int _frame(Image& image, const string& filename){

        int frameSize = 15;
        int frameColorR = 255;
        int frameColorG = 255;
        int frameColorB = 255;

        char choice;
        std::cout << "Enter 's' for a simple frame or 'f' for a fancy frame: ";
        std::cin >> choice;

        if (choice == 's') {
            for (int i = 0; i < image.width; i++) {
                for (int k = 0; k < frameSize; k++) {
                    for (int j = 0; j < frameSize; j++) {
                        image(i, j, 0) = frameColorR;
                        image(i, j, 1) = frameColorG;
                        image(i, j, 2) = frameColorB;
                    }
                    for (int j = image.height - frameSize; j < image.height; j++) {
                        image(i, j, 0) = frameColorR;
                        image(i, j, 1) = frameColorG;
                        image(i, j, 2) = frameColorB;
                    }
                }
                for (int j = frameSize; j < image.height - frameSize; j++) {
                    for (int k = 0; k < frameSize; k++) {
                        for (int i = 0; i < frameSize; i++) {
                            image(i, j, 0) = frameColorR;
                            image(i, j, 1) = frameColorG;
                            image(i, j, 2) = frameColorB;
                        }
                        for (int i = image.width - frameSize; i < image.width; i++) {
                            image(i, j, 0) = frameColorR;
                            image(i, j, 1) = frameColorG;
                            image(i, j, 2) = frameColorB;
                        }
                    }
                }
            }
        } else if (choice == 'f') {
            // Add the simple frame first
            for (int i = 0; i < image.width; i++) {
                for (int k = 0; k < frameSize; k++) {
                    for (int j = 0; j < frameSize; j++) {
                        image(i, j, 0) = frameColorR;
                        image(i, j, 1) = frameColorG;
                        image(i, j, 2) = frameColorB;
                    }
                    for (int j = image.height - frameSize; j < image.height; j++) {
                        image(i, j, 0) = frameColorR;
                        image(i, j, 1) = frameColorG;
                        image(i, j, 2) = frameColorB;
                    }
                }
                for (int j = frameSize; j < image.height - frameSize; j++) {
                    for (int k = 0; k < frameSize; k++) {
                        for (int i = 0; i < frameSize; i++) {
                            image(i, j, 0) = frameColorR;
                            image(i, j, 1) = frameColorG;
                            image(i, j, 2) = frameColorB;
                        }
                        for (int i = image.width - frameSize; i < image.width; i++) {
                            image(i, j, 0) = frameColorR;
                            image(i, j, 1) = frameColorG;
                            image(i, j, 2) = frameColorB;
                        }
                    }
                }
            }

            // Define the fancy frame colors
            int fancyFrameColorR = 0;
            int fancyFrameColorG = 0;
            int fancyFrameColorB = 0;

            // Add fancy patterns to all sides
            for (int i = 0; i < frameSize; ++i) {
                // Dashed lines along the top edge
                if (i % 2 == 0) {
                    for (int j = 0; j < image.width; j += 2) {
                        image(j, i, 0) = fancyFrameColorR;
                        image(j, i, 1) = fancyFrameColorG;
                        image(j, i, 2) = fancyFrameColorB;
                    }
                }

                // Dashed lines along the bottom edge
                if (i % 2 == 0) {
                    for (int j = 0; j < image.width; j += 2) {
                        image(j, image.height - 1 - i, 0) = fancyFrameColorR;
                        image(j, image.height - 1 - i, 1) = fancyFrameColorG;
                        image(j, image.height - 1 - i, 2) = fancyFrameColorB;
                    }
                }

                // Dotted lines along the left edge
                if (i % 3 == 0) {
                    for (int j = 0; j < image.height; j += 3) {
                        image(i, j, 0) = fancyFrameColorR;
                        image(i, j, 1) = fancyFrameColorG;
                        image(i, j, 2) = fancyFrameColorB;
                    }
                }

                // Dotted lines along the right edge
                if (i % 3 == 0) {
                    for (int j = 0; j < image.height; j += 3) {
                        image(image.width - 1 - i, j, 0) = fancyFrameColorR;
                        image(image.width - 1 - i, j, 1) = fancyFrameColorG;
                        image(image.width - 1 - i, j, 2) = fancyFrameColorB;
                    }
                }
            }

            // Add fancy corners
            for (int i = 0; i < frameSize; ++i) {
                for (int j = 0; j < frameSize; ++j) {
                    // Top-left corner
                    image(i, j, 0) = fancyFrameColorR;
                    image(i, j, 1) = fancyFrameColorG;
                    image(i, j, 2) = fancyFrameColorB;

                    // Top-right corner
                    image(image.width - 1 - i, j, 0) = fancyFrameColorR;
                    image(image.width - 1 - i, j, 1) = fancyFrameColorG;
                    image(image.width - 1 - i, j, 2) = fancyFrameColorB;

                    // Bottom-left corner
                    image(i, image.height - 1 - j, 0) = fancyFrameColorR;
                    image(i, image.height - 1 - j, 1) = fancyFrameColorG;
                    image(i, image.height - 1 - j, 2) = fancyFrameColorB;

                    // Bottom-right corner
                    image(image.width - 1 - i, image.height - 1 - j, 0) = fancyFrameColorR;
                    image(image.width - 1 - i, image.height - 1 - j, 1) = fancyFrameColorG;
                    image(image.width - 1 - i, image.height - 1 - j, 2) = fancyFrameColorB;
                }
            }
        } else {
            std::cerr << "Invalid choice. Defaulting to a simple frame." << std::endl;
        }

//
        return 0;
    }


int detect_edges(Image& image, const string& filename) {



        // Check if the image dimensions are valid
        if (image.width <= 0 || image.height <= 0) {
            std::cerr << "Error: Invalid image dimensions." << std::endl;
            return 1; // Return 1 to indicate an error
        }

        // Convert the image to black and white
        for (int i = 0; i < image.width; ++i) {
            for (int j = 0; j < image.height; ++j) {
                // Calculate grayscale value using luminance method (weighted average of RGB channels)
                int gray = (int)(0.2989 * image(i, j, 0) + 0.5870 * image(i, j, 1) + 0.1140 * image(i, j, 2));
                // Thresholding to convert to black and white
                int bw = gray > 128 ? 255 : 0;
                // Assign the black and white value to all three channels
                image(i, j, 0) = bw;
                image(i, j, 1) = bw;
                image(i, j, 2) = bw;
            }
        }

        // Define Sobel operator kernels
        int kernelX[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
        int kernelY[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};

        // Temporary image to store detected edges
        Image tempImage = image;

        // Apply Sobel operator
        for (int i = 1; i < image.width - 1; ++i) {
            for (int j = 1; j < image.height - 1; ++j) {
                // Calculate gradient in x and y directions using Sobel kernels
                int gradientX = 0, gradientY = 0;
                for (int k = -1; k <= 1; ++k) {
                    for (int l = -1; l <= 1; ++l) {
                        gradientX += kernelX[k + 1][l + 1] * image(i + k, j + l, 0);
                        gradientY += kernelY[k + 1][l + 1] * image(i + k, j + l, 0);
                    }
                }
                // Calculate magnitude of the gradient
                int magnitude = (int)sqrt(gradientX * gradientX + gradientY * gradientY);
                // Apply thresholding to emphasize edges
                magnitude = magnitude > 128 ? 255 : 0;
                // Assign the magnitude to temporary image to preserve original
                tempImage(i, j, 0) = magnitude;
                tempImage(i, j, 1) = magnitude;
                tempImage(i, j, 2) = magnitude;
            }
        }

        // Set all pixels to white initially
        for (int i = 0; i < image.width; ++i) {
            for (int j = 0; j < image.height; ++j) {
                image(i, j, 0) = 255;
                image(i, j, 1) = 255;
                image(i, j, 2) = 255;
            }
        }

        // Set the detected edge pixels to black
        for (int i = 1; i < image.width - 1; ++i) {
            for (int j = 1; j < image.height - 1; ++j) {
                if (tempImage(i, j, 0) == 255) {
                    image(i, j, 0) = 0;
                    image(i, j, 1) = 0;
                    image(i, j, 2) = 0;
                }
            }
        }

        // Save the modified image
        int x = image.saveImage("edge_detected_image.jpg");

        // Display message indicating the image has been saved
        std::cout << "Edge-detected image saved successfully." << x<<std::endl;

        return 0;
    }


void resizing_image(Image& image, const std::string& filename) {
    double newWidth, newHeight;

    // Get valid input for new width
    while (true) {
        cout << "Enter new width for resizing: ";
        if (!(cin >> newWidth)) {
            cout << "Invalid input. Please enter a valid number." << endl;
            cin.clear(); // Clear error flags
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
        } else {
            break; // Input is valid, exit the loop
        }
    }

    // Get valid input for new height
    while (true) {
        cout << "Enter new height for resizing: ";
        if (!(cin >> newHeight)) {
            cout << "Invalid input. Please enter a valid number." << endl;
            cin.clear(); // Clear error flags
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
        } else {
            break; // Input is valid, exit the loop
        }
    }

    double ret1 = (image.width) / newWidth;
    double ret2 = (image.height) / newHeight;

    Image newimage(newWidth, newHeight); // Declare new image object

    for (int i = 0; i < newWidth; ++i) {
        for (int j = 0; j < newHeight; ++j) {
            for (int k = 0; k < image.channels; ++k) {
                newimage(i, j, k) = image(i * ret1, j * ret2, k);
            }
        }
    }

    // Assign newimage to image only if the resizing was successful
    image = newimage;
}
 void blur_filter(Image& image, const string& filename){

    int blur_radius = 10;

    for(int i = 0; i < image.width; i++) {
        for(int j = 0; j < image.height; j++) {
            int sum_r = 0, sum_g = 0, sum_b = 0;
            for(int k = -blur_radius; k <= blur_radius; k++) {
                for(int l = -blur_radius; l <= blur_radius; l++) {
                    int x = max(0, std::min(image.width - 1, i + k));
                    int y = max(0, std::min(image.height - 1, j + l));

                    sum_r += image(x, y, 0);
                    sum_g += image(x, y, 1);
                    sum_b += image(x, y, 2);
                }
            }

            int avg_r = sum_r / ((2 * blur_radius + 1) * (2 * blur_radius + 1));
            int avg_g = sum_g / ((2 * blur_radius + 1) * (2 * blur_radius + 1));
            int avg_b = sum_b / ((2 * blur_radius + 1) * (2 * blur_radius + 1));

            image(i, j, 0) = max(0,min(255, avg_r));
            image(i, j, 1) = max(0,min(255, avg_g));
            image(i, j, 2) = max(0, min(255, avg_b));
        }
    }
    image.saveImage("blurred_image.png");
    cout << "Image blurred and saved successfully!" << endl;

}



int sun_light_filter(Image& image, const string& filename){

    // Check if the image was loaded successfully
    bool loadedSuccessfully = true;
    for (int i = 0; i < image.width && loadedSuccessfully; ++i) {
        for (int j = 0; j < image.height && loadedSuccessfully; ++j) {
            for (int k = 0; k < image.channels && loadedSuccessfully; ++k) {
                if (image(i, j, k) == -1) { // Check if any pixel value is invalid (-1)
                    loadedSuccessfully = false;
                }
            }
        }
    }

    if (!loadedSuccessfully) {
        cout << "Error: Failed to load the image." << endl;
        return 1; // Return 1 to indicate an error
    }

    // Apply sun effect to the image
    for (int i = 0; i < image.width; ++i) {
        for (int j = 0; j < image.height; ++j) {
            // Increase brightness of each pixel by multiplying the RGB channels
            // You can adjust the multiplier to control the intensity of the sun effect
            // Red channel
            image(i, j, 0) = min((int)(image(i, j, 0) * 1.05), 255);
            // Green channel
            image(i, j, 1) = min((int)(image(i, j, 1) * 1.08), 255);
            // Blue channel
            image(i, j, 2) = min((int)(image(i, j, 2) * 1.1), 255);
        }
    }

    // Save the modified image
    int x = image.saveImage("sun_impact_image.jpg");

    // Check if the image was saved successfully
    if (x == 0) {
        cout << "Error: Failed to save the image." << endl;
        return 1; // Return 1 to indicate an error
    }

    // Display message indicating the image has been saved
    cout << "Image saved successfully." << x<<endl;

    return 0;
}
void purple_filter(Image& image, const std::string& filename){

    for (int i = 0; i < image.width; ++i) {
        for (int j = 0; j < image.height; ++j) {
            image(i, j, 1) = (int)(image(i, j, 1) * 0.75);
        }
    }


}

void infrared_photography(Image& image, const std::string& filename){

    for(int i = 0; i < image.width; i++){
        for(int j = 0; j < image.height; j++){
            image(i, j, 0) = 230;
            image(i, j, 1) = 255 - image(i, j, 1);
            image(i, j, 2) = 255 - image(i, j, 2);
        }
    }
}















