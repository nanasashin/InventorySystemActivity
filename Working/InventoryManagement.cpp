#include <iostream>
#include <string>
#include <queue>
using namespace std;

const int INVENTORY_MAX_SIZE = 5;

struct Product {
	string name;
	float price;
	int quantity;

	bool is_empty() {
		return name.empty();
	}
};

struct AvailableIndexRange {
	int back_index = 0;
	int front_index = 0;
};

struct TerminalUtils {
public:
	string center_text(string text, int text_max_length) {
		string output = "";

		if (text.length() > text_max_length) {
			for (int i = 0; i < text_max_length; i++) 
				output += text[i];
			return output;
		}
		else if (text.length() == text_max_length) {
			return text;
		}
		
		int left_empty_spaces = (text_max_length - text.length()) / 2;
		int right_empty_spaces = text_max_length - left_empty_spaces - text.length();

		return 
			return_empty_spaces(left_empty_spaces) + 
			text + 
			return_empty_spaces(right_empty_spaces);
	}

	string add_spaces(string text, int length) {
		return text + return_empty_spaces(length - text.length());
	}

	string multiple_char(char character, int lenght) {
		string output;
		for (int i  = 0; i < lenght; i++) {
			output += character;
		}
		return output + "\n";
	}

	int get_digits(int num) {
		int digits = 0;

		while (num != 0) {
			digits += 1;
			num /= 10;
		}

		return digits;
	}

private:
	string return_empty_spaces(int quantity) {
		string output = "";
		for (int i  = 0; i < quantity; i++) {
			output += " ";
		}
		return output;
	}
};

struct InventoryManagement {
private:
	AvailableIndexRange avail_index_range;
	TerminalUtils terminal_utils;

	const Product empty_prod = Product{};
	const int collumn_sizes[3] = {20, 20, 20};
	const int inventory_max_length = terminal_utils.get_digits(INVENTORY_MAX_SIZE);

	Product inventory_arr[INVENTORY_MAX_SIZE];
	queue<int> queue;

public:
	void remove_last_product() {
		if (queue.empty()) {
			cout << "< Invalid: Can not remove in a empty inventory >\n";
			return;
		}

		int removing_index = queue.front();

		avail_index_range.front_index = removing_index;
		inventory_arr[removing_index] = empty_prod;
		queue.pop();

		cout << "Product Removed Successful\n";
	}

	void add_product(Product product) {
		int index;

		if (queue.size() == INVENTORY_MAX_SIZE) {
			cout << "< Invalid: Inventory is full >\n";
			return;
		}

		if (queue.empty()) {
			index = 0;
		}
		else if (!inventory_arr[INVENTORY_MAX_SIZE - 1].is_empty()) {
			index = avail_index_range.back_index;
			avail_index_range.back_index += 1;
		}
		else {
			index = queue.back() + 1;
		}

		inventory_arr[index] = product;
		queue.push(index);

		cout << "Product Added Successful\n";
	}

	void display_last_product() {
		int last_product_index = queue.front();
		cout << "Product Details\n";
		cout << "    Name :" << inventory_arr[last_product_index].name << "\n";
		cout << "   Price :" << inventory_arr[last_product_index].price << "\n";
		cout << "Quantity :" << inventory_arr[last_product_index].quantity << "\n\n";
	}

	void display_products () {
		for (int i = 0; i < INVENTORY_MAX_SIZE; i++) {
			if (!inventory_arr[i].is_empty()) {
				print_item(i, inventory_arr[i]);
			}
			else {
				print_empty();
			}
		}
	}

	void update_product(int index, Product product) {
		if (inventory_arr[index].is_empty()) {
			cout << "Invalid: Inventory index is empty\n";
			return;
		}

		inventory_arr[index] = product;

		cout << "Product Updated Succesful\n";
	}

	bool inventory_is_empty() {
		return (queue.empty());
	}

private:
	bool back_have_available_index() {
		if (avail_index_range.back_index != avail_index_range.front_index) 
			return true;
		return false;
	}

	void print_display_header() {
		cout << "|" << terminal_utils.add_spaces("", inventory_max_length) << "|";
		cout << terminal_utils.center_text("Product Name", collumn_sizes[0]) << "|";
		cout << terminal_utils.center_text("Price", collumn_sizes[1]) << "|";
		cout << terminal_utils.center_text("Quantity", collumn_sizes[2]) << "|\n";

		int char_length = collumn_sizes[0] + collumn_sizes[1] + collumn_sizes[2] + 4;
		cout << terminal_utils.multiple_char('-', char_length);
	}

	void print_item(int index, Product product) {
		string output[3];

		output[0] = terminal_utils.center_text(product.name, collumn_sizes[0]);
		output[1] = terminal_utils.center_text(std::to_string(product.price), collumn_sizes[0]);
		output[2] = terminal_utils.center_text(std::to_string(product.quantity), collumn_sizes[0]);

		cout << "|" << terminal_utils.center_text(to_string(index), inventory_max_length);
		cout << "|" << output[0] << "|" << output[1] << "|" << output[2] << "|\n";
	}

	void print_empty() {
		cout << "|" << terminal_utils.center_text("empty", collumn_sizes[0]) << "|";
		cout << terminal_utils.center_text("empty", collumn_sizes[1]) << "|";
		cout << terminal_utils.center_text("empty", collumn_sizes[2]) << "|\n";
	}
};

int main() {
	InventoryManagement inventory_management;
	int front_page_input;
	bool program_running = true;

	
	while (program_running) {
		cout << "==============================\n\n";
		cout << "[1] Add Product\n";
		cout << "[2] Remove Last Product\n";
		cout << "[3] Update Product\n";
		cout << "[4] Exit Product\n\n";

		cout << "Input: ";
		cin >> front_page_input;
	
		if (front_page_input == 1) {
			Product add_product;

			cout << "\nProduct Name: ";
			cin.ignore();
			getline(cin, add_product.name);

			cout << "Product Price: ";
			cin >> add_product.price;

			cout << "Product Quantity: ";
			cin >> add_product.quantity;

			inventory_management.add_product(add_product);
			cout << "\n";
		}
		else if (front_page_input == 2) {
			inventory_management.display_last_product();

			while (true) {
				char input;
				cout << "\n";

				if (inventory_management.inventory_is_empty()) {
					cout << "\n< Inventory is Empty >\n\n";
					break;
				}

				cout << "\nRemove product [Y/n]: ";
				cin >> input;
	
				if (input == 'Y' || input == 'y') {
					inventory_management.remove_last_product();
				}
				else if (input == 'N' || input == 'n') {
					cout << "\nDeletion Cancel\n\n";
					break;
				}
				else {
					cout << "\n< Invalid Input >\n\n";
				}
			}
		}
		else if (front_page_input == 3) {
			inventory_management.display_products();
			cout << "\n";
		}
		else if (front_page_input == 4) {
			cout << "\nExiting Program\n\n";
			program_running = false;
		}
		else {
			cout << "Invalid Input < Try Again >\n";
		}
	}
}