#ifndef UISYSTEM_HPP_
#define UISYSTEM_HPP_

#include <iostream>
#include <limits>

#include "Product.hpp"
#include "InventorySystem.hpp"

using namespace std;

struct System {
public:	
	enum class UpdateType {
		ADD,
		SUBTRACT,
		CHANGE
	};

	enum class Attribute {
		QUANTITY,
		PRICE
	};

	int front_page() {
		cout << "[1] Add Product";
		cout << "[2] Remove Product";
		cout << "[3] Update Product";
		cout << "[4] Quit Program";
		return get_input<int>();
	}

	void add_product() {
		if (!inventory_system.inventory_full()) {
			Product temp;
			temp.name = get_input<string>("Input Product Name");
			temp.price = get_input<float>("Input Product Price");
			temp.quantity = get_input<int>("Input Product Quantity");
		}
		else {
			cout << "Inventory Full";
		}
	}

	void update_product() {
		int index = get_input<int>("Input Inventory Index");

		cout << "[1] Change Quantity\n";
		cout << "[2] Change Price\n";
		cout << "[3] Change Name\n";
		cout << "[4] Exit\n";

		int input = get_input<int>();

		switch (input)
		{
		case 1:
			break;
		
		default:
			break;
		}
	}

	int pick_product() {
		return get_input<int>("Product Index");
	}

	int remove_product() {
		return get_input<int>("Delete Inventory at Index");
	}

private:
	InventorySystem inventory_system;

	template<typename T>
	T get_input(string text = "Input", string error_msg = "<Invalid Input>") {
		T input;
		
		while (true) {
			cout << text << ": ";
			if (cin >> input) {
				break;
			}
			else {
				cout << "\n" << error_msg << "\n\n";
				cin.clear();
				cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			}
		}

		int sample[] = {1, 2, 3};

		loop_array(sample);

		return input;
	}

	void update(int index, UpdateType update_type, Attribute attribute) {
		Product product = inventory_system.get_product(index);
		float value;
		float input;

		while (true) {
			switch (attribute) 
			{
			case Attribute::QUANTITY:
				cout << "Current Quantity -> " << product.quantity << "\n\n";
				input = get_input<int>("Update Quantity [-1 to exit]");
				break;
			
			case Attribute::PRICE:
				cout << "Current Price -> " << product.price << "\n\n";
				input = get_input<int>("Update Price [-1 to exit]");
				break;
			}
	
			if (input > -1) {
				cout << "\n<Invalid Range>\n\n";
			}
			else if (input == -1) {
				return;
			}
			else {
				break;
			}
		}

		switch (update_type) 
		{
		case UpdateType::ADD:
			value += input;
			break;
		
		case UpdateType::SUBTRACT:
			value -= input;
			break;

		case UpdateType::CHANGE:
			value = input;
			break;
		}

		switch (attribute) 
		{
		case Attribute::QUANTITY:
			product.quantity = value;
			break;
		
		case Attribute::PRICE:
			product.price = value;
			break;
		}

		inventory_system.update_product(index, product);
	}

	string return_string_with_space(string text, int max_length) {
		int add_spaces = max_length - text.length();
		for (int i = 0; i < add_spaces; i++) {
			text += " ";
		}
		return text;
	}

	void print_inventory() {
		cout << "| Product Name |  Quantity  |  Price  |\n";
		for (int i = 0; i < inventory_system.get_inv_max(); i++) {
			Product curr_prod = inventory_system.get_product(i);

		}
	}
};

#endif
