#include <iostream>

enum tree_type {
	pre_order,
	in_order,
	post_order,
};

template<typename T, typename Compare = std::less<T>, typename Allocator = std::allocator<T>>
class BinarySearchTree {
private:
	inline static int order;
	class Tree_node;
	friend class Tree_node;
	int count = 0;
	class Tree_node {
	public:
		friend class BinarySearchTree<T>;
		friend class iterator;

		T value; 

		Tree_node(T node_value) : value(node_value) {}
		Tree_node() {}
		~Tree_node() {}

		void print_value() { std::cout << value << std::endl; }

		Tree_node* right;
		Tree_node* left;
		Tree_node* parent;
	};

	Compare compare;
	using MainAllocator = typename std::allocator_traits<Allocator>::template rebind_alloc<Tree_node>;
	MainAllocator allocator;
public:
	class iterator;
	friend class iterator;
	class const_iterator {
		friend class BinarySearchTree<T>;

	public:

		const const_iterator() :cur_node(0) {} // ������� �����������

		const const_iterator(Tree_node* node) : cur_node(node) {} // ��������� �� ���� node

		const const_iterator(const const_iterator& copy_iterator) : cur_node(copy_iterator.cur_node) {}

		const const_iterator& operator=(const const_iterator& it) {
			cur_node = it.cur_node;
			return *this;
		}


		const bool operator == (const const_iterator& it) const {
			return (cur_node == it.cur_node);
		}

		const bool operator!=(const const_iterator& it) const {
			return !(it == *this);
		}

		const const_iterator& operator--() {
			if (order == tree_type::pre_order) {
				preOrderDec();
			}
			else if (order == tree_type::in_order) {
				inOrderDec();
			}
			else {
				postOrderDec();
			}

			return *this;
		}

		const const_iterator& operator++() {
			if (order == tree_type::pre_order) {
				preOrder();
			}
			else if (order == tree_type::in_order) {
				inOrder();
			}
			else {
				postOrder();
			}
			return *this;
		}

		const void preOrderDec() {
			if (cur_node->parent == 0) {
				cur_node = root_iterator.cur_node;
				while (cur_node->left != 0 || cur_node->right != 0) {
					if (cur_node->right != 0) {
						cur_node = cur_node->right;
					}
					else {
						cur_node = cur_node->left;
					}
				}
				return;
			}

			if (cur_node->parent->left == cur_node) {
				cur_node = cur_node->parent;
			}
			else {
				Tree_node* current = cur_node->parent;

				if (current->left != 0) {
					current = current->left;
					while (current->left != 0 || current->right != 0) {
						if (current->right != 0) {
							current = current->right;
						}
						else {
							current = current->left;
						}
					}
				}
				cur_node = current;
			}
		}

		const void preOrder() {
			if (cur_node->left != 0) {
				cur_node = cur_node->left;
			}
			else if (cur_node->right != 0) {
				cur_node = cur_node->right;
			}
			else {
				Tree_node* current = cur_node->parent;

				while (current->left != 0 || current->right != 0) {
					if (current->right == 0 || current->right == cur_node) {
						cur_node = current;
						current = current->parent;
					}
					else {
						current = current->right;
						break;
					}
				}

				cur_node = current;
			}
		}

		const void inOrder() {
			if (cur_node->parent == 0) {
				cur_node = root_iterator.cur_node;
				while (cur_node->left != 0) {
					cur_node = cur_node->left;
				}
				return;
			}
			if (cur_node->right != 0) {
				Tree_node* current = cur_node->right;
				while (current->left != 0) {
					current = current->left;
				}
				cur_node = current;
			}
			else {
				Tree_node* current = cur_node->parent;

				while (current->left != 0 || current->right != 0) {
					if (current->right == 0 || current->right != cur_node) {
						break;
					}
					cur_node = current;
					current = current->parent;
				}

				cur_node = current;
			}
		}

		const void inOrderDec() {
			if (cur_node->parent == 0) {
				cur_node = root_iterator.cur_node;
				while (cur_node->right != 0) {
					if (cur_node->right != 0) {
						cur_node = cur_node->right;
					}
				}
				return;
			}
			if (cur_node->left != 0) {
				cur_node = cur_node->left;

				while (cur_node->right != 0) {
					cur_node = cur_node->right;
				}
			}
			else if (cur_node->parent != 0 && cur_node->parent->right == cur_node) {
				cur_node = cur_node->parent;
			}
			else if (cur_node->parent != 0 && cur_node->parent->left != 0 && cur_node->parent->left == cur_node) {
				Tree_node* current = cur_node->parent;

				while (current->right != 0 && current->right != cur_node) {
					cur_node = current;
					current = current->parent;
				}

				cur_node = current;
			}

		}

		const void postOrder() {
			if (cur_node->parent->right == 0 || cur_node->parent->right == cur_node) {
				cur_node = cur_node->parent;
			}
			else {
				Tree_node* current = cur_node->parent->right;

				while (current->left != 0 || current->right != 0) {
					if (current->left != 0) {
						current = current->left;
					}
					else {
						current = current->right;
					}

				}

				cur_node = current;
			}
		}

		const void postOrderDec() {
			if (cur_node->parent == 0) {
				cur_node = root_iterator.cur_node;
				return;
			}

			if (cur_node->right != 0) {
				cur_node = cur_node->right;
			}
			else if (cur_node->left != 0) {
				cur_node = cur_node->left;
			}
			else {
				Tree_node* current = cur_node->parent;

				while (current->left != 0 && current->left == cur_node) {
					cur_node = current;
					current = current->parent;
				}

				cur_node = current;
				if (current->left != 0) {
					cur_node = current->left;
				}
			}
		}

		const T& operator*() const {
			if (cur_node == 0) {
				throw "trying to dereference an empty iterator";
			}

			return cur_node->value;
		}

	private:
		Tree_node* cur_node;
	};

	class const_reverse_iterator {
		friend class BinarySearchTree<T>;

	public:

		const const_reverse_iterator() :cur_node(0) {} // ������� �����������

		const const_reverse_iterator(Tree_node* node) : cur_node(node) {} // ��������� �� ���� node

		const const_reverse_iterator(const const_reverse_iterator& copy_iterator) : cur_node(copy_iterator.cur_node) {}

		const const_reverse_iterator& operator=(const const_reverse_iterator& it) {
			cur_node = it.cur_node;
			return *this;
		}


		const bool operator == (const const_reverse_iterator& it) const {
			return (cur_node == it.cur_node);
		}

		const bool operator!=(const const_reverse_iterator& it) const {
			return !(it == *this);
		}

		const const_reverse_iterator& operator--() {
			if (order == tree_type::pre_order) {
				preOrder();
			}
			else if (order == tree_type::in_order) {
				inOrder();
			}
			else {
				postOrder();
			}

			return *this;
		}

		const const_reverse_iterator& operator++() {
			if (order == tree_type::pre_order) {
				preOrderDec();
			}
			else if (order == tree_type::in_order) {
				inOrderDec();
			}
			else {
				postOrderDec();
			}

			return *this;
		}

		const void preOrderDec() {
			if (cur_node->parent == 0) {
				cur_node = root_iterator.cur_node;
				while (cur_node->left != 0 || cur_node->right != 0) {
					if (cur_node->right != 0) {
						cur_node = cur_node->right;
					}
					else {
						cur_node = cur_node->left;
					}
				}
				return;
			}

			if (cur_node->parent->left == cur_node) {
				cur_node = cur_node->parent;
			}
			else {
				Tree_node* current = cur_node->parent;

				if (current->left != 0) {
					current = current->left;
					while (current->left != 0 || current->right != 0) {
						if (current->right != 0) {
							current = current->right;
						}
						else {
							current = current->left;
						}
					}
				}
				cur_node = current;
			}
		}

		const void preOrder() {
			if (cur_node->parent == 0) {
				cur_node = root_iterator.cur_node;
				return;
			}
			if (cur_node->left != 0) {
				cur_node = cur_node->left;
			}
			else if (cur_node->right != 0) {
				cur_node = cur_node->right;
			}
			else {
				Tree_node* current = cur_node->parent;

				while (current->left != 0 || current->right != 0) {
					if (current->right == 0 || current->right == cur_node) {
						cur_node = current;
						current = current->parent;
					}
					else {
						current = current->right;
						break;
					}
				}

				cur_node = current;
			}
		}

		void inOrder() {
			if (cur_node->parent == 0) {
				cur_node = root_iterator.cur_node;
				while (cur_node->left != 0) {
					cur_node = cur_node->left;
				}
				return;
			}
			if (cur_node->right != 0) {
				Tree_node* current = cur_node->right;
				while (current->left != 0) {
					current = current->left;
				}
				cur_node = current;
			}
			else {
				Tree_node* current = cur_node->parent;

				while (current->left != 0 || current->right != 0) {
					if (current->right == 0 || current->right != cur_node) {
						break;
					}

					cur_node = current;
					current = current->parent;
				}

				cur_node = current;
			}
		}

		const void inOrderDec() {
			if (cur_node->parent == 0) {
				cur_node = root_iterator.cur_node;
				while (cur_node->right != 0) {
					if (cur_node->right != 0) {
						cur_node = cur_node->right;
					}
				}
				return;
			}
			if (cur_node->left != 0) {
				cur_node = cur_node->left;

				while (cur_node->right != 0) {
					cur_node = cur_node->right;
				}
			}
			else if (cur_node->parent != 0 && cur_node->parent->right == cur_node) {
				cur_node = cur_node->parent;
			}
			else if (cur_node->parent != 0 && cur_node->parent->left != 0 && cur_node->parent->left == cur_node) {
				Tree_node* current = cur_node->parent;

				while (current->right != 0 && current->right != cur_node) {
					cur_node = current;
					current = current->parent;
				}

				cur_node = current;
			}

		}

		const void postOrder() {
			if (cur_node->parent == 0) {
				cur_node = root_iterator.cur_node;
				while (cur_node->right != 0 || cur_node->left != 0) {
					if (cur_node->left != 0) {
						cur_node = cur_node->left;
					} else {
						cur_node = cur_node->right;
					}
				}

				return;
			}
			if (cur_node->parent->right == 0 || cur_node->parent->right == cur_node) {
				cur_node = cur_node->parent;
			}
			else {
				Tree_node* current = cur_node->parent->right;

				while (current->left != 0 || current->right != 0) {
					if (current->left != 0) {
						current = current->left;
					}
					else {
						current = current->right;
					}

				}

				cur_node = current;
			}
		}

		const void postOrderDec() {
			if (cur_node->parent == 0) {
				cur_node = root_iterator.cur_node;
				return;
			}

			if (cur_node->right != 0) {
				cur_node = cur_node->right;
			}
			else if (cur_node->left != 0) {
				cur_node = cur_node->left;
			}
			else {
				Tree_node* current = cur_node->parent;

				while (current->left != 0 && current->left == cur_node) {
					cur_node = current;
					current = current->parent;
				}

				cur_node = current;
				if (current->left != 0) {
					cur_node = current->left;
				}
			}
		}

		const T& operator*() const {
			if (cur_node == 0) {
				throw "trying to dereference an empty iterator";
			}

			return cur_node->value;
		}

	private:
		Tree_node* cur_node;
	};

	class reverse_iterator {
		friend class BinarySearchTree<T>;

	public:

		reverse_iterator() :cur_node(0) {} // ������� �����������

		reverse_iterator(Tree_node* node) : cur_node(node) {} // ��������� �� ���� node

		reverse_iterator(const reverse_iterator& copy_iterator) : cur_node(copy_iterator.cur_node) {}

		reverse_iterator& operator=(const reverse_iterator& it) {
			cur_node = it.cur_node;
			return *this;
		}


		bool operator == (const reverse_iterator& it) const {
			return (cur_node == it.cur_node);
		}

		bool operator!=(const reverse_iterator& it) const {
			return !(it == *this);
		}

		reverse_iterator& operator--() {
			if (order == tree_type::pre_order) {
				preOrder();
			}
			else if (order == tree_type::in_order) {
				inOrder();
			}
			else {
				postOrder();
			}

			return *this;
		}

		reverse_iterator& operator++() {
			if (order == tree_type::pre_order) {
				preOrderDec();
			}
			else if (order == tree_type::in_order) {
				inOrderDec();
			}
			else {
				postOrderDec();
			}

			return *this;
		}

		void preOrderDec() {
			if (cur_node->parent == 0) {
				cur_node = root_iterator.cur_node;
				while (cur_node->left != 0 || cur_node->right != 0) {
					if (cur_node->right != 0) {
						cur_node = cur_node->right;
					}
					else {
						cur_node = cur_node->left;
					}
				}
				return;
			}

			if (cur_node->parent->left == cur_node) {
				cur_node = cur_node->parent;
			}
			else {
				Tree_node* current = cur_node->parent;

				if (current->left != 0) {
					current = current->left;
					while (current->left != 0 || current->right != 0) {
						if (current->right != 0) {
							current = current->right;
						}
						else {
							current = current->left;
						}
					}
				}
				cur_node = current;
			}
		}

		void preOrder() {
			if (cur_node->parent == 0) {
				cur_node = root_iterator.cur_node;
				return;
			}
			if (cur_node->left != 0) {
				cur_node = cur_node->left;
			}
			else if (cur_node->right != 0) {
				cur_node = cur_node->right;
			}
			else {
				Tree_node* current = cur_node->parent;

				while (current->left != 0 || current->right != 0) {
					if (current->right == 0 || current->right == cur_node) {
						cur_node = current;
						current = current->parent;
					}
					else {
						current = current->right;
						break;
					}
				}

				cur_node = current;
			}
		}

		void inOrder() {
			if (cur_node->parent == 0) {
				cur_node = root_iterator.cur_node;
				while (cur_node->left != 0) {
					cur_node = cur_node->left;
				}
				return;
			}
			if (cur_node->right != 0) {
				Tree_node* current = cur_node->right;
				while (current->left != 0) {
					current = current->left;
				}
				cur_node = current;
			} else {
				Tree_node* current = cur_node->parent;

				while (current->left != 0 || current->right != 0) {
					if (current->right == 0 || current->right != cur_node) {
						break;
					}

					cur_node = current;
					current = current->parent;
				}

				cur_node = current;
			}
		}

		void inOrderDec() {
			if (cur_node->parent == 0) {
				cur_node = root_iterator.cur_node;
				while (cur_node->right != 0) {
					if (cur_node->right != 0) {
						cur_node = cur_node->right;
					}
				}
				return;
			}
			if (cur_node->left != 0) {
				cur_node = cur_node->left;

				while (cur_node->right != 0) {
					cur_node = cur_node->right;
				}
			}
			else if (cur_node->parent != 0 && cur_node->parent->right == cur_node) {
				cur_node = cur_node->parent;
			}
			else if (cur_node->parent != 0 && cur_node->parent->left != 0 && cur_node->parent->left == cur_node) {
				Tree_node* current = cur_node->parent;

				while (current->right != 0 && current->right != cur_node) {
					cur_node = current;
					current = current->parent;
				}

				cur_node = current;
			}

		}

		void postOrder() {
			if (cur_node->parent == 0) {
				cur_node = root_iterator.cur_node;
				while (cur_node->right != 0 || cur_node->left != 0) {
					if (cur_node->left != 0) {
						cur_node = cur_node->left;
					}
					else {
						cur_node = cur_node->right;
					}
				}

				return;
			}
			if (cur_node->parent->right == 0 || cur_node->parent->right == cur_node) {
				cur_node = cur_node->parent;
			}
			else {
				Tree_node* current = cur_node->parent->right;

				while (current->left != 0 || current->right != 0) {
					if (current->left != 0) {
						current = current->left;
					}
					else {
						current = current->right;
					}

				}

				cur_node = current;
			}
		}

		void postOrderDec() {
			if (cur_node->parent == 0) {
				cur_node = root_iterator.cur_node;
				return;
			}

			if (cur_node->right != 0) {
				cur_node = cur_node->right;
			}
			else if (cur_node->left != 0) {
				cur_node = cur_node->left;
			}
			else {
				Tree_node* current = cur_node->parent;

				while (current->left != 0 && current->left == cur_node) {
					cur_node = current;
					current = current->parent;
				}

				cur_node = current;
				if (current->left != 0) {
					cur_node = current->left;
				}
			}
		}

		T& operator*() const {
			if (cur_node == 0) {
				throw "trying to dereference an empty iterator";
			}

			return cur_node->value;
		}

	private:
		Tree_node* cur_node;
	};

	class iterator {
		friend class BinarySearchTree<T>;

	public:
		
		iterator() :cur_node(0) {} // ������� �����������

		iterator(Tree_node* node) : cur_node(node) {} // ��������� �� ���� node

		iterator(const iterator& copy_iterator) : cur_node(copy_iterator.cur_node) {}

		iterator& operator=(const iterator& it) {
			cur_node = it.cur_node;
			return *this;
		}


		bool operator == (const iterator& it) const {
			return (cur_node == it.cur_node);
		}

		bool operator!=(const iterator& it) const {
			return !(it == *this);
		}

		iterator& operator--() {
			if (order == tree_type::pre_order) {
				preOrderDec();
			} else if (order == tree_type::in_order) {
				inOrderDec();
			} else {
				postOrderDec();
			}

			return *this;
		}

		iterator& operator++() {
			if (order == tree_type::pre_order) {
				preOrder();
			} else if (order == tree_type::in_order) {
				inOrder();
			} else {
				postOrder();
			}
			return *this;
		}

		void preOrderDec() {
			if (cur_node->parent == 0) {
				cur_node = root_iterator.cur_node;
				while (cur_node->left != 0 || cur_node->right != 0) {
					if (cur_node->right != 0) {
						cur_node = cur_node->right;
					} else {
						cur_node = cur_node->left;
					}
				}
				return;
			}

			if (cur_node->parent->left == cur_node) {
				cur_node = cur_node->parent;
			} else {
				Tree_node* current = cur_node->parent;

				if (current->left != 0) {
					current = current->left;
					while (current->left != 0 || current->right != 0) {
						if (current->right != 0) {
							current = current->right;
						}
						else {
							current = current->left;
						}
					}
				}
				cur_node = current;
			}
		}

		void preOrder() { 
			if (cur_node->left != 0) {
				cur_node = cur_node->left;
			} else if (cur_node->right != 0) {
				cur_node = cur_node->right;
			} else {
				Tree_node* current = cur_node->parent;

				while (current->left != 0 || current->right != 0) {
					if (current->right == 0 || current->right == cur_node) {
						cur_node = current;
						current = current->parent;
					} else {
						current = current->right;
						break;
					}
				}

				cur_node = current;
			}
		}

		void inOrder() {
			if (cur_node->parent == 0) {
				cur_node = root_iterator.cur_node;
				while (cur_node->left != 0) {
					cur_node = cur_node->left;
				}
				return;
			}
			if (cur_node->right != 0) {
				Tree_node* current = cur_node->right;
				while (current->left != 0) {
					current = current->left;
				}
				cur_node = current;
			}
			else {
				Tree_node* current = cur_node->parent;

				while (current->left != 0 || current->right != 0) {
					if (current->right == 0 || current->right != cur_node) {
						break;
					}

					cur_node = current;
					current = current->parent;
				}

				cur_node = current;
			}
		}

		void inOrderDec() {
			if (cur_node->parent == 0) {
				cur_node = root_iterator.cur_node;
				while (cur_node->right != 0) {
					if (cur_node->right != 0) {
						cur_node = cur_node->right;
					}
				}
				return;
			}
			if (cur_node->left != 0) {
				cur_node = cur_node->left;

				while (cur_node->right != 0) {
					cur_node = cur_node->right;
				}
			} else if (cur_node->parent != 0 && cur_node->parent->right == cur_node) {
				cur_node = cur_node->parent;
			} else if (cur_node->parent != 0 && cur_node->parent->left != 0 && cur_node->parent->left == cur_node) {
				Tree_node* current = cur_node->parent;

				while (current->right != 0 && current->right != cur_node) {
					cur_node = current;
					current = current->parent;
				}

				cur_node = current;
			}

		}

		void postOrder() {
			if (cur_node->parent->right == 0 || cur_node->parent->right == cur_node) {
				cur_node = cur_node->parent;
			} else {
				Tree_node* current = cur_node->parent->right;

				while (current->left != 0 || current->right != 0) {
					if (current->left != 0) {
						current = current->left;
					} else {
						current = current->right;
					}

				}

				cur_node = current;
			}
		}

		void postOrderDec() {
			if (cur_node->parent == 0) {
				cur_node = root_iterator.cur_node;
				return;
			}

			if (cur_node->right != 0) {
				cur_node = cur_node->right;
			}
			else if (cur_node->left != 0) {
				cur_node = cur_node->left;
			}
			else {
				Tree_node* current = cur_node->parent;

				while (current->left != 0 && current->left == cur_node) {
					cur_node = current;
					current = current->parent;
				}

				cur_node = current;
				if (current->left != 0) {
					cur_node = current->left;
				}
			}
		}

		T& operator*() const {
			if (cur_node == 0) {
				throw "trying to dereference an empty iterator";
			}

			return cur_node->value;
		}

	private:
		Tree_node* cur_node;
	};

private:
	Tree_node* root;
	Tree_node* end_node;

	inline static iterator root_iterator;
	iterator end_iterator;
	const_iterator end_citerator;
	reverse_iterator end_riterator;
	const_reverse_iterator end_criterator;
	bool is_empty = true;

public:
	BinarySearchTree(tree_type need_order) {
		order = need_order;
		end_node = root = std::allocator_traits<MainAllocator>::allocate(allocator, 1);

		root->left = root->right = root->parent = nullptr;
		is_empty = true;

		root_iterator = iterator(root);
		end_iterator = iterator(root);
		end_citerator = const_iterator(root);
		end_riterator = reverse_iterator(root);
		end_criterator = const_reverse_iterator(root);
	}

	BinarySearchTree(T node_value, tree_type need_order) {
		order = need_order;
		end_node = root = std::allocator_traits<MainAllocator>::allocate(allocator, 1);
		root->left = root->right = root->parent = nullptr;
		is_empty = true;

		root_iterator = iterator(root);
		end_iterator = iterator(root);
		end_citerator = const_iterator(root);
		end_riterator = reverse_iterator(root);
		end_criterator = const_reverse_iterator(root);
		Insert(node_value);
	}

	~BinarySearchTree() {
		if (!is_empty) {
			DeleteTree(root);
		}
		allocator.deallocate(end_node, 1);
	}

	iterator end() { return end_iterator; }
	const_iterator cend() { return end_citerator; }
	reverse_iterator rend() { return end_riterator; }
	const_reverse_iterator crend() { return end_criterator; }

	iterator begin() {
		if (order == tree_type::pre_order || is_empty) {
			return root_iterator;
		} else {
			Tree_node *current = root;
			
			if (order == tree_type::in_order) {
				while (current->left != 0) {
					current = current->left;
				}
			} else {
				while (current->left != 0 || current->right != 0) {
					if (current->left != 0) {
						current = current->left;
					} else {
						current = current->right;
					}
				}
			}

			iterator it = iterator(current);

			return it;
		}
	} 

	const_iterator cbegin() {
		return const_iterator(begin().cur_node);
	}

	reverse_iterator rbegin() {
		if (is_empty) {
			return rend();
		}

		if (order == tree_type::post_order) {
			return reverse_iterator(root_iterator.cur_node);
		} else if (order == tree_type::in_order) {
			Tree_node* current = root;

			while (root->right != 0) {
				root = root->right;
			}

			return reverse_iterator(root);
		} else {
			Tree_node* current = root;

			while (root->right != 0 || root->left != 0) {
				if (root->right == 0) {
					root = root->left;
				} else {
					root = root->right;
				}
			}

			return reverse_iterator(root);
		}
	}

	const_reverse_iterator crbegin() {
		return const_reverse_iterator(rbegin().cur_node);
	}

	bool IsExistValue(T node_value) {
		return find(node_value) != end();
	}

	void DeleteTree(Tree_node* node) {
		if (node->left != 0) {
			DeleteTree(node->left);
		} 

		if (node->right != 0) {
			DeleteTree(node->right);
		}

		allocator.deallocate(node, 1);
	}

	bool empty() const {
		return is_empty;
	}
	bool contains(T value) const {
		return find(value) != end_iterator;
	}

	int size() const {
		return count;
	}

	void clear() {
		count = 0;
		if (!is_empty) {
			DeleteTree(root);
		}
	}

	void Insert(T node_value) {
		count++;
		if (is_empty) {
			is_empty = false;
			root = std::allocator_traits<MainAllocator>::allocate(allocator, 1);
			std::allocator_traits<MainAllocator>::construct(allocator, root, node_value);
			root->left = root->right = root->parent = nullptr;
			root->parent = end_node;

			root_iterator = iterator(root);
		} else {
			Tree_node *current = root;

			while (1) {
				if (compare(current->value, node_value)) {
					if (current->right == 0) {
						current->right = std::allocator_traits<MainAllocator>::allocate(allocator, 1);
						std::allocator_traits<MainAllocator>::construct(allocator, current->right, node_value);
						current->right->left = current->right->right = nullptr;
						current->right->parent = current;

						break;
					} 
					current = current->right;
				} else {
					if (current->left == 0) {
						current->left = std::allocator_traits<MainAllocator>::allocate(allocator, 1);
						std::allocator_traits<MainAllocator>::construct(allocator, current->left, node_value);
						current->left->left = current->left->right = nullptr;
						current->left->parent = current;

						break;
					}
					current = current->left;
				}
			}
		}
	}

	iterator find(T node_value) const {
		if (is_empty) {
			return end_iterator;
		}

		Tree_node* current = root;
		
		while (compare(current->value, node_value) || compare(node_value, current->value)) {
			if (compare(current->value, node_value)) {
				if (current->right == 0) {
					break;
				}

				current = current->right;
			}
			else {
				if (current->left == 0) {
					break;
				}

				current = current->left;
			}
		}

		if (compare(current->value, node_value) || compare(node_value, current->value)) {
			return end_iterator;
		}

		iterator result = iterator(current);
		return result;
	}

	const_iterator cfind(T node_value) const {
		return const_iterator(find(node_value).cur_node);
	}

	reverse_iterator rfind(T node_value) const {
		return reverse_iterator(find(node_value).cur_node);
	}
	const_reverse_iterator crfind(T node_value) const {
		return const_reverse_iterator(find(node_value).cur_node);
	}

	void Delete(T node_value) {
		count--;
		if (is_empty) {
			throw "trying delete in empty tree";
		}

		iterator current_iterator = find(node_value);

		if (current_iterator == end_iterator) {
			throw "trying delete don`t exist value";
		}

		Tree_node* current = current_iterator.cur_node;

		while (current->left != 0 || current->right != 0) {
			if (current->left != 0 && current->right == 0) {
				Tree_node* left = current->left;
				current->value = current->left->value;
				current->right = current->left->right;
				current->left = current->left->left;

				allocator.deallocate(left, 1);

				if (current->left != 0) {
					current->left->parent = current;
				}

				if (current->right != 0) {
					current->right->parent = current;
				}

				return;
			}

			if (current->left == 0 && current->right != 0) {
				Tree_node* right = current->right;
				current->value = current->right->value;
				current->left = current->right->left;
				current->right = current->right->right;

				allocator.deallocate(right, 1);
				if (current->left != 0) {
					current->left->parent = current;
				}
				if (current->right != 0) {
					current->right->parent = current;
				}

				return;
			}

			if (current->right->left == 0) {
				Tree_node* right = current->right;
				current->value = current->right->value;
				current->right = current->right->right;

				allocator.deallocate(right, 1);
				if (current->right != 0) {
					current->right->parent = current;
				}

				return;
			}

			Tree_node* new_del = std::allocator_traits<MainAllocator>::allocate(allocator, 1);
			while (new_del->left != 0) {
				new_del = new_del->left;
			}

			current->value = new_del->value;

			current = new_del;
		}

		if (current == root) {
			is_empty = true;
			allocator.deallocate(current, 1);
			root_iterator = end_iterator;
			return;
		}
		if (current->parent->left == current) {
			current->parent->left = 0;
		}
		else {
			current->parent->right = 0;
		}

		allocator.deallocate(current, 1);
	}
};