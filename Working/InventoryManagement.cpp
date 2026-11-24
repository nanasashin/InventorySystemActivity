#include <iostream>
#include <string>
#include <queue>
using namespace std;

const int INVENTORY_MAX_SIZE = 11;
string front_message = "";
string global_line = "=============================";

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
	void clear_screen() {
		std::cout << "\033[2J\033[H" << std::flush;
	}

	string center_text(string text, int text_max_length) {
		string output = "";

		if (text.length() > text_max_length) {
			for (int i = 0; i < text_max_length; i++) {
				output += text[i];
			}
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

	string left_text(string text, int length) {
		return text + return_empty_spaces(length - text.length());
	}

	string right_text(string text, int length) {
		return return_empty_spaces(length - text.length()) + text;
	}

	string multiple_char(char character, int lenght) {
		string output;
		for (int i  = 0; i < lenght; i++) {
			output += character;
		}
		return output + "\n";
	}

	string delete_suffix(string text, int amount) {
		int keep = text.length() - amount;
		string output = "";
		for (int i = 0; i < keep; i++) {
			output += text[i];
		}
		return output;
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
} terminal_utils;

struct InventoryManagement {
private:
	AvailableIndexRange avail_index_range;

	const Product empty_prod = Product{};
	const int collumn_sizes[3] = {20, 20, 20};
	const int inventory_max_length = terminal_utils.get_digits(INVENTORY_MAX_SIZE - 1);

	Product inventory_arr[INVENTORY_MAX_SIZE];
	queue<int> queue;

public:
	void remove_last_product() {
		if (queue.empty()) {
			cout << "\n< Invalid: Can not remove in a empty inventory >\n";
			return;
		}

		int removing_index = queue.front();

		avail_index_range.front_index = removing_index;
		inventory_arr[removing_index] = empty_prod;
		queue.pop();

		front_message = "Product Removed Successful";
	}

	void add_product(Product product) {
		int index;

		if (queue.size() == INVENTORY_MAX_SIZE) {
			cout << "\n< Invalid: Inventory is full >\n\n";
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

		front_message = "Product Added Successful";
	}

	void display_last_product() {
		display_product(queue.front());
	}

	void display_product(int index) {
		cout << "Product Details at Index # " << index << "\n\n";
		cout << "Name     : " << inventory_arr[index].name << "\n";
		cout << "Price    : " << inventory_arr[index].price << "\n";
		cout << "Quantity : " << inventory_arr[index].quantity << "\n\n";
	}

	void display_products () {
		cout << "\n";

		print_display_header();

		for (int i = 0; i < INVENTORY_MAX_SIZE; i++) {
			cout << "|" << terminal_utils.right_text(to_string(i), inventory_max_length);

			if (!inventory_arr[i].is_empty()) {
				print_item(i, inventory_arr[i]);
			}
			else {
				print_empty();
			}
		}

		print_table_line();
		cout << "\n";
	}

	void update_product(int index, Product product) {
		if (inventory_arr[index].is_empty()) {
			cout << "\nInvalid: Inventory index is empty\n\n";
			return;
		}

		inventory_arr[index] = product;

		cout << "\nProduct Updated Succesful\n\n";
	}

	bool inventory_is_empty() {
		return (queue.empty());
	}

	bool index_is_empty(int index) {
		return inventory_arr[index].is_empty();
	}

	bool inventory_full() {
		return queue.size() == INVENTORY_MAX_SIZE;
	}

	Product get_product(int index) {
		return inventory_arr[index];
	}

private:
	bool back_have_available_index() {
		if (avail_index_range.back_index != avail_index_range.front_index) 
			return true;
		return false;
	}

	void print_display_header() {
		print_table_line();

		cout << " " << terminal_utils.left_text("", inventory_max_length) << "|";
		cout << terminal_utils.center_text("Product Name", collumn_sizes[0]) << "|";
		cout << terminal_utils.center_text("Price", collumn_sizes[1]) << "|";
		cout << terminal_utils.center_text("Quantity", collumn_sizes[2]) << "|\n";

		print_table_line();
	}

	void print_table_line() {
		int char_length = collumn_sizes[0] + collumn_sizes[1] + collumn_sizes[2] + 5 + inventory_max_length;
		cout << terminal_utils.multiple_char('-', char_length);
	}

	void print_item(int index, Product product) {
		string output[3];

		output[0] = terminal_utils.center_text(product.name, collumn_sizes[0]);
		output[1] = terminal_utils.center_text(
			"$ " + terminal_utils.delete_suffix(to_string(product.price), 4), 
			collumn_sizes[0]
		);
		output[2] = terminal_utils.center_text(to_string(product.quantity), collumn_sizes[0]);

		cout << "|" << output[0] << "|" << output[1] << "|" << output[2] << "|\n";
	}

	void print_empty() {
		cout << "|" << terminal_utils.center_text("empty", collumn_sizes[0]) << "|";
		cout << terminal_utils.center_text("empty", collumn_sizes[1]) << "|";
		cout << terminal_utils.center_text("empty", collumn_sizes[2]) << "|\n";
	}

} inventory_management;

void handle_add_product() {
	if (inventory_management.inventory_full()) {
		front_message ="< Inventory full >";
		return;
	}

	Product add_product;

	cout << "\nProduct Name: ";
	cin.ignore();
	getline(cin, add_product.name);

	cout << "Product Price: ";
	cin >> add_product.price;

	cout << "Product Quantity: ";
	cin >> add_product.quantity;

	inventory_management.add_product(add_product);
}

void handle_removing_product() {
	cout << "\n";

	if (inventory_management.inventory_is_empty()) {
		front_message = "< Inventory is Empty >";
		return;
	}

	inventory_management.display_last_product();

	while (true) {
		char input;

		cout << "Remove product [Y/n]: ";
		cin >> input;

		if (input == 'Y' || input == 'y') {
			inventory_management.remove_last_product();
			break;
		}
		else if (input == 'N' || input == 'n') {
			break;
		}
		else {
			cout << "\n< Invalid Input >\n\n";
		}
	}
}

void handle_updating_product() {
	bool update_running = true;

	while (true) {
		start:
		int index;

		if (inventory_management.inventory_is_empty()) {
			front_message = "Inventory is Empty";
			break;
		}
	
		inventory_management.display_products();
	
		cout << "Input index to update [-1 to exit]: ";
		cin >> index;

		if (index == -1) {
			cout << "\nExiting Update\n\n";
			break;
		}

		if (inventory_management.index_is_empty(index)) {
			cout << "\n< Index is Empty >\n\n";
			goto start;
		}

		Product initial_product = inventory_management.get_product(index);
		int attribute;
		string changes;

		cout << "\nChange Attribute:\n";
		cout << "[1] Name\n";
		cout << "[2] Price\n";
		cout << "[3] Quantity\n";
		cout << "[4] Exit Updating\n\n";

		cout << "Input: ";
		cin >> attribute;
	
		cout << "\nChange Value: ";
		cin >> changes;

		switch (attribute) 
		{
		case 1:
			initial_product.name = changes;
			break;
		case 2:
			initial_product.price = stof(changes);
			break;
		case 3:
			initial_product.quantity = stoi(changes);
			break;
		case 4:
			update_running = false;
		default:
			break;
		}

		if (!update_running) {
			break;
		}

		inventory_management.update_product(index, initial_product);
		inventory_management.display_product(index);

		terminal_utils.clear_screen();
		cout << "\n" << global_line <<"\n";
		cout << terminal_utils.center_text("UPDATE PRODUCT", global_line.length());
		cout << "\n" << global_line <<"\n";
	}
}

void handle_display_product() {
	inventory_management.display_products();

	std::cin.ignore();
	cout << "Press Enter to exit: ";
	cin.get();
}

int main() {
	int front_page_input;
	bool program_running = true;
	string line = global_line;
	string page_header[5] = {
		terminal_utils.center_text("INVENTORY SYSTEM", line.length()),		
		terminal_utils.center_text("ADD PRODUCT", line.length()),
		terminal_utils.center_text("REMOVE PRODUCT", line.length()),
		terminal_utils.center_text("UPDATE PRODUCT", line.length()),
		terminal_utils.center_text("DISPLAY PRODUCTS", line.length()),
	};

	while (program_running) {
		terminal_utils.clear_screen();

		cout << "\n" << line <<"\n";
		cout << page_header[0] << "\n";

		if (!front_message.empty()) {
			cout << line <<"\n";
			cout << terminal_utils.center_text(front_message, line.length()) << "\n";
			front_message = "";
		}

		cout << line <<"\n\n";
		cout << "[1] Add Product\n";
		cout << "[2] Remove Last Product\n";
		cout << "[3] Update Product\n";
		cout << "[4] Display Products\n";
		cout << "[5] Exit Program\n\n";

		cout << "Input: ";
		cin >> front_page_input;

		terminal_utils.clear_screen();

		cout << "\n" << line <<"\n";
		cout << page_header[front_page_input];
		cout << "\n" << line <<"\n";
	
		switch (front_page_input){
		case 1:
			handle_add_product();
			break;
		case 2:
			handle_removing_product();
			break;
		case 3:
			handle_updating_product();
			break;
		case 4:
			handle_display_product();
			break;
		case 5:
			program_running = false;
			break;
		default:
			front_message = "Invalid Input < Try Again >";
			break;
		}
	}

	terminal_utils.clear_screen();
	cout << "\n" << line <<"\n";
	cout << terminal_utils.center_text("< - - - Program Ended - - - >", line.length());
	cout << "\n" << line <<"\n";
}