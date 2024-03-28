/*
Name: Mohamed alaa eldeen asmai ibrahim       ID: 20230346
Name: Abdelrahman Ashraf Mohamed Mostafa      ID: 20230610
Name: Mostafa Abdelgalel Ahmed salama         ID: 20230403
*/

#include <iostream>
#include "Image_Class.h"
#include <string>
#include <cmath>
#include <vector>

using namespace std;

bool validation_extentionimage(const string &imagename) {
    if (imagename.find(".jpg") != string::npos ||
        imagename.find(".jpeg") != string::npos ||
        imagename.find(".png") != string::npos ||
        imagename.find(".bmp") != string::npos) {

    }
    else {
        cout << "the extension of the image is incorrect" << endl;
        return false;
    }
}

void save_image(string &newimagename){

    cout << "please type the name of the new image" << endl;
    cout << "Notice: the extension of the image should be end with JPEG, JPG, PNG, or BMP" << endl;
    cout << "Notice: if you typed the name and there is an image have the same name the modified image will replace the old one" << endl;
    cout << "type the name of the image:";

    getline(cin , newimagename);
    if(!validation_extentionimage(newimagename)){
    }
     cout << "the image has been saved " << endl;
}

int asking_for_exist (string &imagename){

    string option_exist , option_save ;

    cout << "do you want to exist : type (1) for yes , type (2) for no" << endl;
    getline(cin , option_exist);

    while(true){

        if(option_exist == "1"){
            cout << "do you want to save before exist , to save type (1) , to ignore type (2)" << endl;
            getline(cin , option_save);

            while (true){
                if(option_save == "1"){
                    save_image(imagename);
                    return 1;
                    break;
                }
                else if (option_save == "2"){
                    cout << "Thank you for using out program" << endl;
                    return 2;
                    break;
                }
                else {
                    cout << "please type a valid choice" << endl;
                    break;
                }
            }
            break;

        }
        else if (option_exist == "2"){
            save_image(imagename);
            return 3;
            break;
        }
        else cout << "please type a valid choice" << endl;
        break;
    }

}

Image Gray_Image(const string &imagename) {
    Image image(imagename);

    for (int i = 0; i < image.width; i++) {
        for (int j = 0; j < image.height; j++) {
            unsigned int avg = 0;

            for (int k = 0; k < 3; k++) {
                avg += image(i, j, k);
            }

            avg /= 3;

            for (int k = 0; k < 3; k++) {
                image(i, j, k) = avg;
            }
        }
    }
    return image;
}

Image black_and_white(const string &imagename){
    Image image;
    Image image2;

    if (image2.loadNewImage(imagename)) {
        cout << "Image loaded successfully\n";
    }

    for (int i = 0; i < image2.width; ++i) {
        for (int j = 0; j < image2.height; ++j) {
            // Calculate weighted average for black and white conversion
            double luma = 0.2126 * image2(i, j, 0) + 0.7152 * image2(i, j, 1) + 0.0722 * image2(i, j, 2);  // Common luma weights

            // Apply weighted average to all channels with some adjustment
            unsigned int gray = static_cast<unsigned int>(luma * 1.1);  // Adjust for slightly brighter blacks

            // Restrict gray value to valid range (0-255)
            gray = min(gray, 255u);

            for (int k = 0; k < 3; ++k) {
                image2(i, j, k) = gray;
            }
        }
    }

    for (int i = 0; i < image2.width; ++i) {
        for (int j = 0; j < image2.height; ++j) {
            for (int k = 0; k < 3; ++k) {
                if(image2(i,j,k) >= 100){
                    image2(i,j,k) = 255;
                }
                else
                    image2(i,j,k) = 0 ;
            }
        }
    }
    return image2 ;
}

Image flip_image_vertical(const string &imagename){

    Image image;
    Image image2;

    if (image2.loadNewImage(imagename)) {
        cout << "Image loaded successfully.\n";
    } else {
        cout << "Failed to load the image.\n";
    }

    // Flip vertically
    for (int i = 0; i < image2.width; ++i) {
        for (int j = 0; j < image2.height / 2; ++j) {
            for (int k = 0; k < image2.channels; ++k) {
                swap(image2(i, j, k), image2(i, image2.height - 1 - j, k));
            }
        }
    }
    return image2 ;
}
Image flip_image_horizontal(const string &imagename){

    Image image;
    Image image2;

    if (image2.loadNewImage(imagename)) {
        cout << "Image loaded successfully.\n";
    } else {
        cout << "Failed to load the image.\n";
    }
    // Flip horizontally
    for (int i = 0; i < image2.width / 2; ++i) {
        for (int j = 0; j < image2.height; ++j) {
            for (int k = 0; k < image2.channels; ++k) {
                swap(image2(i, j, k), image2(image2.width - 1 - i, j, k));
            }
        }
    }
    return image2;
}

Image  inverted_image (const string &imagename){
    Image image(imagename);
    unsigned int pixel_color;
    unsigned int inverted_color;
    for (int i = 0; i < image.width; ++i) {
        for (int j = 0; j < image.height; ++j) {
            for (int k = 0; k < 3; ++k) {
                pixel_color = image.getPixel(i,j,k);
                inverted_color = 0 - pixel_color;
                image(i,j,k) = inverted_color;
            }
        }
    }
    return image;
}

// Function to increase the lightness of an image
Image increase_light_image(const string &imagename) {
    Image image(imagename);

    for (int i = 0; i < image.width; i++) {
        for (int j = 0; j < image.height; j++) {
            for (int k = 0; k < 3; k++) {

                // Increase the pixel value by 50% of its current value
                image(i,j,k) = min(255 , image(i,j,k)+64);
            }
        }
    }
    return image ;
}
Image decrease_light_image(const string &imagename){
    Image image(imagename);

     for (int i = 0; i < image.width; i++) {
        for (int j = 0; j < image.height; j++) {
            for (int k = 0; k < 3; k++) {

                // decrease the pixel value by 50% of its current value
                image(i,j,k) = max(0 , image(i,j,k)-64);
            }
        }
    }
    return image ;
}


int main() {

    string imagename , option , newimagename;

    while (true){

        cout << "Please type the name of the image:" ;

        getline(cin , imagename);
        if(!validation_extentionimage(imagename)){
            continue;
        }

        cout << "please type the number of the filter you want" << endl;
        cout << "Enter (1) for Grayscale Conversion filter" << endl;
        cout << "Enter (2) for Black and White filter" << endl;
        cout << "Enter (3) for Invert Image filter" << endl;
        cout << "Enter (4) for Darken and Lighten Image filter" << endl;
        cout << "Enter (5) for Flip Image" << endl;
        cout << "Enter (6) to exist from the program" << endl;
        cout << "Enter the number of the filter:";

        getline(cin , option);

        if(option == "1"){

            Image image = Gray_Image(imagename);
            cout << "the image has been generated successfully " << endl;

            int exist_choice = asking_for_exist(imagename);
            if (exist_choice == 1) {
                image.saveImage(imagename);
                break;
            } else if (exist_choice == 2) {
                break;
            } else if (exist_choice == 3) {
                image.saveImage(imagename);
                // Do nothing, just continue the loop
            }
        }
        else if (option == "2"){

            Image image = black_and_white(imagename);
            cout << "the image has been generated successfully " << endl;


            int exist_choice = asking_for_exist(imagename);
            if (exist_choice == 1) {
                image.saveImage(imagename);
                break;
            } else if (exist_choice == 2) {
                break;
            } else if (exist_choice == 3) {
                image.saveImage(imagename);
                // Do nothing, just continue the loop
            }

        }
        else if (option == "3"){

            Image image = inverted_image(imagename);
            cout << "the image has been generated successfully " << endl;


            int exist_choice = asking_for_exist(imagename);
            if (exist_choice == 1) {
                image.saveImage(imagename);
                break;
            } else if (exist_choice == 2) {
                break;
            } else if (exist_choice == 3) {
                image.saveImage(imagename);
                // Do nothing, just continue the loop
            }


        }
        else if (option == "4"){

            string option_light ;
            cout << "if you want to increase the light type (1) , to decrease the light type (2)" << endl;
            cout << "Enter your choice : ";

            getline(cin , option_light);

            if(option_light == "1"){

                //call the increase light function
                Image image = increase_light_image(imagename);
                cout << "the image has been generated successfully " << endl;


                int exist_choice = asking_for_exist(imagename);
                if (exist_choice == 1) {
                    image.saveImage(imagename);
                    break;
                } else if (exist_choice == 2) {
                    break;
                } else if (exist_choice == 3) {
                    image.saveImage(imagename);
                    // Do nothing, just continue the loop
                }
            }

            else if (option_light == "2"){

                //call the decrease light function
                Image image = decrease_light_image(imagename);
                cout << "the image has been generated successfully " << endl;


                int exist_choice = asking_for_exist(imagename);
                if (exist_choice == 1) {
                    image.saveImage(imagename);
                    break;
                } else if (exist_choice == 2) {
                    break;
                } else if (exist_choice == 3) {
                    image.saveImage(imagename);
                    // Do nothing, just continue the loop
                }
            }
            else{

                cout << "please type a valid choice" << endl;
                break;
            }
        }

        else if (option == "5"){

            string flip_direction;
            cout << "Do you want to flip the image vertically or horizontally? (vertical/horizontal): " << endl;
            cout << "type (1) for vertical , type (2) for horizontal" << endl;
            cout << "Enter you choice : " ;
            getline(cin , flip_direction);

            if (flip_direction == "1"){

                Image image = flip_image_vertical(imagename);
                cout << "the image has been generated successfully " << endl;

                int exist_choice = asking_for_exist(imagename);
                if (exist_choice == 1) {
                    image.saveImage(imagename);
                    break;
                } else if (exist_choice == 2) {
                    break;
                } else if (exist_choice == 3) {
                    image.saveImage(imagename);
                    // Do nothing, just continue the loop
                }
            }
            else if (flip_direction == "2"){

                Image image = flip_image_horizontal(imagename);
                cout << "the image has been generated successfully " << endl;

                int exist_choice = asking_for_exist(imagename);
                if (exist_choice == 1) {
                    image.saveImage(imagename);
                    break;
                } else if (exist_choice == 2) {
                    break;
                } else if (exist_choice == 3) {
                    image.saveImage(imagename);
                    // Do nothing, just continue the loop
                }
            }
            else {
                cout << "please type a valid choice" << endl;
                break;
            }
        }
        else if (option == "6"){
            cout << "thank you for using our program" << endl;
            break;
        }
        else{
            cout << "please Enter a valid choice" << endl;
        }

    }
}

