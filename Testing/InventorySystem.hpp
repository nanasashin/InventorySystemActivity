#ifndef INVENTORYSYSTEM_HPP_
#define INVENTORY_HPP_

#include "Product.hpp"

using namespace std;

struct InventorySystem {
public:
	InventorySystem() {
		for (int i = 0; i < inv_max_product; i++) {
			set_availability(i, true);
			add_product_to_inventory(i, Product{});
		}
	}

	Product get_product(int index) {
		return inventory[index];
	}

	bool add_product_index(int index, Product product) {
		if (index_is_available(index)) {
			add_product_to_inventory(index, product);
			return true;
		}
		else {
			return false;
		}
	}

	bool add_product_auto(Product product) {
		int available_index = return_available_index();
		if (available_index != -1) {
			add_product_to_inventory(available_index, product);
			return true;
		}
		else {
			return false;
		}
	}

	bool remove_product(int index) {
		if (!index_is_available(index)) {
			remove_product_to_inventory(index);
			return true;
		}
		else {
			return false;
		}
	}

	bool update_product(int index, Product Product) {
		add_product_to_inventory(index, Product);
	}

	bool inventory_full() {
		if (return_available_index() != -1) {
			return true;
		}
		return false;
	}

	bool index_is_available(int index) {
		return product_availability[index];
	}

	int get_inv_max() {
		return inv_max_product;
	}


private:
	static const int inv_max_product = 100;

	Product inventory[inv_max_product];
	Product empty_product;

	bool product_availability[inv_max_product];

	void set_availability(int index, bool status) {
		product_availability[index] = status;
	}

	void add_product_to_inventory(int index, Product product) {
		inventory[index] = product;
		set_availability(index, false);
	}
	
	void remove_product_to_inventory(int index) {
		inventory[index] = empty_product;
		set_availability(index, true);
	}

	int return_available_index() {
		for (int i = 0; i < inv_max_product; i++) {
			if (index_is_available(i)) {
				return i;
			}
		}
		return - 1;
	}
};

#endif