#include <iostream>
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

struct InventoryManagement {
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
				std::cout 
				<< inventory_arr[i].name << " "
				<< inventory_arr[i].price << " "
				<< inventory_arr[i].quantity << "\n\n";
			}
			else {
				std::cout << "Empty\n\n";
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
	const Product empty_prod = Product{};

	AvailableIndexRange avail_index_range;

	Product inventory_arr[INVENTORY_MAX_SIZE];
	std::queue<int> queue;

	bool back_have_available_index() {
		if (avail_index_range.back_index != avail_index_range.front_index) 
			return true;
		return false;
	}
};

int main() {
	InventoryManagement inventory_management;
	Product sample_product = Product{"sample", 1, 1};

	inventory_management.display_products();

}