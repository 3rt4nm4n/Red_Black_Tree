using namespace std;

template <class T> 
class RBNode
{
private:
	bool isRed;
	T value;
	RBNode<T> *left, *right, *parent;
public:
	RBNode(T value)
	{
		this->isRed = true;
		this->value = value;
		left = NULL;
		right = NULL;
		parent = NULL;
	}
	void Recolor()
	{
		if (this->isRed) this->isRed = false;
		else this->isRed = true;
	}
	bool IsRed()
	{
		return isRed;
	}
	T GetValue()
	{
		return this->value;
	}
	RBNode* GetLeft()
	{
		return this->left;
	}
	RBNode* GetRight()
	{
		return this->right;
	}
	RBNode* GetParent()
	{
		return this->parent;
	}
	void ClearParent()
	{
		this->parent = NULL;
	}
	void SetLeft(RBNode* left)
	{
		this->left = left;
		if(left != NULL) left->parent = this;
	}
	void SetRight(RBNode* right)
	{
		this->right = right;
		if(right != NULL) right->parent = this;
	}
};

template <class T> class RedBlackTree
{
private:
	RBNode<T>* root;

	RBNode<T>* AccessNode(RBNode<T> *root, T value)
	{
		if(root->GetValue() == value) 
		{
			return root;
		}
		else if(root->GetValue() > value)
		{
			if(root->GetLeft() == NULL)
			{
				return NULL;
			}
			else
			{
				return this->AccessNode(root->GetLeft(), value);
			}
		}
		else
		{
			if(root->GetRight() == NULL)
			{
				return NULL;
			}
			else
			{
				return this->AccessNode(root->GetRight(), value);
			}
		}
	}
	void InsertNode(RBNode<T> *root, T value)
	{
		RBNode<T>* insertedNode = NULL;
		if(root->GetValue() == value)
		{
			//skip
		}
		else if(root->GetValue() > value)
		{
			if(root->GetLeft() == NULL)
			{
				insertedNode = new RBNode<T>(value);
				root->SetLeft(insertedNode);
			}
			else
			{
				this->InsertNode(root->GetLeft(), value);
			}
		}
		else
		{
			if(root->GetRight() == NULL)
			{
				insertedNode = new RBNode<T>(value);
				root->SetRight(insertedNode);
			}
			else
			{
				this->InsertNode(root->GetRight(), value);
			}
		}
		if (insertedNode == NULL) return;
		this->SolveDoubleRedProblem(root);
		insertedNode = NULL;
	}
	
	void SolveDoubleRedProblem(RBNode<T> *root)
	{
		if (root->IsRed() == false) return;
		if (root == root->GetParent()->GetLeft())
		{
			if (root->GetParent()->GetRight() == NULL || !root->GetParent()->GetRight()->IsRed()) this->RightRotate(root);
			else
			{
				root->Recolor();
				root->GetParent()->GetRight()->Recolor();
				root->GetParent()->Recolor();
				if (root->GetParent()->GetParent() == NULL)
				{
					root->GetParent()->Recolor();
					return;
				}
				SolveDoubleRedProblem(root->GetParent()->GetParent());
			}
		}
		else
		{
			if (root->GetParent()->GetLeft() == NULL || !root->GetParent()->GetLeft()->IsRed()) this->LeftRotate(root);
			else
			{
				root->Recolor();
				root->GetParent()->GetLeft()->Recolor();
				root->GetParent()->Recolor();
				if (root->GetParent()->GetParent() == NULL)
				{
					root->GetParent()->Recolor();
					return;
				}
				SolveDoubleRedProblem(root->GetParent()->GetParent());
			}
		}
	}
	void LeftRotate(RBNode<T> *root)
	{
		RBNode<T> *parent = root->GetParent();
		if (root->GetLeft() != NULL && root->GetLeft()->IsRed())
		{
			RBNode<T> *badChild = root->GetLeft();
			root->SetLeft(badChild->GetRight());
			badChild->SetRight(root);
			parent->SetRight(badChild);
			root = badChild;
		}
		root->Recolor();
		parent->Recolor();
		parent->SetRight(root->GetLeft());
		if (parent->GetParent() != NULL)
		{
			if (parent->GetParent()->GetLeft() == parent) parent->GetParent()->SetLeft(root);
			else parent->GetParent()->SetRight(root);
		}
		else
		{
			this->root = root;
			this->root->ClearParent();
			root = this->root;
		}
		root->SetLeft(parent);
	}
	void RightRotate(RBNode<T> *root)
	{
		RBNode<T> *parent = root->GetParent();
		if (root->GetRight() != NULL && root->GetRight()->IsRed())
		{
			RBNode<T> *badChild = root->GetRight();
			root->SetRight(badChild->GetLeft());
			badChild->SetLeft(root);
			parent->SetLeft(badChild);
			root = badChild;
		}
		root->Recolor();
		parent->Recolor();
		parent->SetLeft(root->GetRight());
		if (parent->GetParent() != NULL)
		{
			if (parent->GetParent()->GetLeft() == parent) parent->GetParent()->SetLeft(root);
			else parent->GetParent()->SetRight(root);
		}
		else
		{
			this->root = root;
			this->root->ClearParent();
			root = this->root;
		}
		root->SetRight(parent);
	}
	

public:
	RedBlackTree()
	{
		this->root = NULL;
	}
	bool IsEmpty()
	{
		return root == NULL;
	}
	RBNode<T>* AccessNode(T value)
	{
		if (this->IsEmpty()) return NULL;
		else return this->AccessNode(root, value);
	}
	void InsertNode(T value)
	{
		if (this->IsEmpty())
		{
			this->root = new RBNode<T>(value);
			this->root->Recolor();
		}
		else this->InsertNode(this->root, value);
	}

};
