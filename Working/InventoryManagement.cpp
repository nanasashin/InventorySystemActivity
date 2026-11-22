#include <iostream>
#include <string>
#include <queue>

const int INVENTORY_MAX_SIZE = 5;

struct Product {
	std::string name;
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
	std::string center_text(std::string text, int text_max_length) {
		std::string output = "";

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

	std::string add_spaces(std::string text, int length) {
		return text + return_empty_spaces(length - text.length());
	}

	std::string multiple_char(char character, int lenght) {
		std::string output;
		for (int i  = 0; i < lenght; i++) {
			output += character;
		}
		return output + "\n";
	}

private:
	std::string return_empty_spaces(int quantity) {
		std::string output = "";
		for (int i  = 0; i < quantity; i++) {
			output += " ";
		}
		return output;
	}
};

struct InventoryManagement {
private:
	const Product empty_prod = Product{};
	const int collumn_sizes[3] = {20, 20, 20};

	AvailableIndexRange avail_index_range;
	TerminalUtils terminal_utils;

	Product inventory_arr[INVENTORY_MAX_SIZE];
	std::queue<int> queue;

public:
	void remove_last_product() {
		if (queue.empty()) {
			std::cout << "Invalid: Can not remove in a empty inventory\n";
			return;
		}

		int removing_index = queue.front();

		avail_index_range.front_index = removing_index;
		inventory_arr[removing_index] = empty_prod;
		queue.pop();

		std::cout << "Product Removed Successful\n";
	}

	void add_product(Product product) {
		int index;

		if (queue.size() == INVENTORY_MAX_SIZE) {
			std::cout << "Invalid: Inventory is full\n";
			return;
		}

		// Picking what index to store the product
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

		std::cout << "Product Added Successful\n";
	}

	void display_products () {
		for (int i = 0; i < INVENTORY_MAX_SIZE; i++) {
			if (!inventory_arr[i].is_empty()) {
				print_item(inventory_arr[i]);
			}
			else {
				print_empty();
			}
		}
	}

	void update_product(int index, Product product) {
		if (inventory_arr[index].is_empty()) {
			std::cout << "Invalid: Inventory index is empty\n";
			return;
		}

		inventory_arr[index] = product;

		std::cout << "Product Updated Succesful\n";
	}

private:
	bool back_have_available_index() {
		if (avail_index_range.back_index != avail_index_range.front_index) 
			return true;
		return false;
	}

	void print_display_header() {
		std::cout << "|" 
			<< terminal_utils.center_text("Product Name", collumn_sizes[0]) << "|"
			<< terminal_utils.center_text("Price", collumn_sizes[1]) << "|"
			<< terminal_utils.center_text("Quantity", collumn_sizes[2]) << "|\n"
		;
		int char_length = collumn_sizes[0] + collumn_sizes[1] + collumn_sizes[2] + 4;
		std::cout << terminal_utils.multiple_char('-', char_length);
	}

	void print_item(Product product) {
		std::string output[3];

		output[0] = terminal_utils.center_text(product.name, collumn_sizes[0]);
		output[1] = terminal_utils.center_text(std::to_string(product.price), collumn_sizes[0]);
		output[2] = terminal_utils.center_text(std::to_string(product.quantity), collumn_sizes[0]);

		std::cout << "|" << output[0] << "|" << output[1] << "|" << output[2] << "|\n";
	}

	void print_empty() {
		std::cout << "|" 
			<< terminal_utils.center_text("empty", collumn_sizes[0]) << "|"
			<< terminal_utils.center_text("empty", collumn_sizes[1]) << "|"
			<< terminal_utils.center_text("empty", collumn_sizes[2]) << "|\n"
		;
	}
};

int main() {
	InventoryManagement inventory_management;
	
}