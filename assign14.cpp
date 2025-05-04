#include <iostream>
#include <fstream>
#include <string>

using namespace std;

struct Product {
    int id;
    char name[50];
    float price;

    void display() const {
        cout << "ID: " << id << ", Name: " << name << ", Price: " << price << endl;
    }
};


void writeProduct(const char* filename, const Product& product, int position) {
    fstream outFile(filename, ios::binary | ios::in | ios::out);
    if (!outFile) {
        cerr << "Error opening file for writing!" << endl;
        return;
    }
    outFile.seekp(position * sizeof(Product), ios::beg);
    outFile.write((char*)&product, sizeof(Product));
    outFile.close();
}


Product readProduct(const char* filename, int position) {
    Product product{};
    ifstream inFile(filename, ios::binary);
    if (!inFile) {
        cerr << "Error opening file for reading!" << endl;
        return product;
    }
    inFile.seekg(position * sizeof(Product), ios::beg);
    inFile.read((char*)&product, sizeof(Product));
    inFile.close();
    return product;
}


void addProduct(const char* filename) {
    Product product;
    cout << "Enter Product ID: ";
    cin >> product.id;
    cin.ignore();
    cout << "Enter Product Name: ";
    cin.getline(product.name, 50);
    cout << "Enter Product Price: ";
    cin >> product.price;

    ofstream outFile(filename, ios::binary | ios::app);
    if (!outFile) {
        cerr << "Error opening file for appending!" << endl;
        return;
    }
    outFile.write((char*)&product, sizeof(Product));
    outFile.close();
    cout << "Product added successfully!" << endl;
}


void viewProducts(const char* filename) {
    ifstream inFile(filename, ios::binary);
    if (!inFile) {
        cerr << "Error opening file for reading!" << endl;
        return;
    }

    Product product;
    cout << "Products in the file:" << endl;
    while (inFile.read((char*)&product, sizeof(Product))) {
        product.display();
    }
    inFile.close();
}


void updateProduct(const char* filename) {
    int position;
    cout << "Enter the position of the product to update (0-based index): ";
    cin >> position;

    Product product;
    cout << "Enter new Product ID: ";
    cin >> product.id;
    cin.ignore();
    cout << "Enter new Product Name: ";
    cin.getline(product.name, 50);
    cout << "Enter new Product Price: ";
    cin >> product.price;

    writeProduct(filename, product, position);
    cout << "Product updated successfully!" << endl;
}


void deleteProduct(const char* filename) {
    int position;
    cout << "Enter the position of the product to delete (0-based index): ";
    cin >> position;

    ifstream inFile(filename, ios::binary);
    if (!inFile) {
        cerr << "Error opening file for reading!" << endl;
        return;
    }

    ofstream tempFile("temp.dat", ios::binary);
    if (!tempFile) {
        cerr << "Error creating temporary file!" << endl;
        inFile.close();
        return;
    }

    Product product;
    int currentPos = 0;

    while (inFile.read((char*)&product, sizeof(Product))) {
        if (currentPos != position) {
            tempFile.write((char*)&product, sizeof(Product));
        }
        currentPos++;
    }

    inFile.close();
    tempFile.close();

    
    remove(filename);
    rename("temp.dat", filename);

    cout << "Product deleted successfully!" << endl;
}

int main() {
    const char* filename = "products.dat";
    int choice;

    do {
        cout << "\n--- Product Management Menu ---\n";
        cout << "1. Add Product\n";
        cout << "2. View Products\n";
        cout << "3. Update Product\n";
        cout << "4. Delete Product\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                addProduct(filename);
                break;
            case 2:
                viewProducts(filename);
                break;
            case 3:
                updateProduct(filename);
                break;
            case 4:
                deleteProduct(filename);
                break;
            case 5:
                cout << "Exiting the program. Goodbye!" << endl;
                break;
            default:
                cout << "Invalid choice! Please try again." << endl;
        }
    } while (choice != 5);

    return 0;
}
