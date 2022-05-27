#include "tree.h"

Tree::Node* Tree::Insert(Node* tree, std::pair<std::string, char> pr1, int i)
{
  if (tree == nullptr)
  {
    tree = new Node(pr1);
  }
  else  if (pr1.first[i] == '-')   // if the next character is '-' going to the left
  {
    tree->Left = Insert(tree->Left, pr1, (i < pr1.first.size()) ? ++i : i);
  }
  else                 // if the next character is '.' going to the right
  {
    tree->Right = Insert(tree->Right, pr1, (i < pr1.first.size()) ? ++i : i);
  }
  return tree;
}


void Tree::Find(Node* Tree, std::string value, int i, char& res)
{
  if (value == Tree->pr.first)
  {
    res = Tree->pr.second;
  }
  else
  {
    if (value[i] == '-')
    {
      Find(Tree->Left, value, (i < value.size()) ? ++i : i, res);
    }
    else
    {
      Find(Tree->Right, value, (i < value.size()) ? ++i : i, res);
    }
  }
}

void Tree::Free(Node* tree)
{
    if (tree != nullptr)
    {
        Free(tree->Left);
        Free(tree->Right);
        delete tree;
        tree = nullptr;
    }
}

Tree::Node* Tree::Insert()
{
    Tree::Insert(this->node, { "-",'t' }, 0);
    Tree::Insert(this->node, { ".",'e' }, 0);
    Tree::Insert(this->node, { "--",'m' }, 0);
    Tree::Insert(this->node, { "-.",'n' }, 0);
    Tree::Insert(this->node, { ".-",'a' }, 0);
    Tree::Insert(this->node, { "..",'i' }, 0);
    Tree::Insert(this->node, { "---",'o' }, 0);
    Tree::Insert(this->node, { "--.",'g' }, 0);
    Tree::Insert(this->node, { "-.-",'k' }, 0);
    Tree::Insert(this->node, { "-..",'d' }, 0);
    Tree::Insert(this->node, { ".--",'w' }, 0);
    Tree::Insert(this->node, { ".-.",'r' }, 0);
    Tree::Insert(this->node, { "..-",'u' }, 0);
    Tree::Insert(this->node, { "...", 's' }, 0);
    Tree::Insert(this->node, { "--.-",'q' }, 0);
    Tree::Insert(this->node, { "--..",'z' }, 0);
    Tree::Insert(this->node, { "-.--",'y' }, 0);
    Tree::Insert(this->node, { "-.-.",'c' }, 0);
    Tree::Insert(this->node, { "-..-",'x' }, 0);
    Tree::Insert(this->node, { "-...",'b' }, 0);
    Tree::Insert(this->node, { ".---",'j' }, 0);
    Tree::Insert(this->node, { ".--.",'p' }, 0);
    Tree::Insert(this->node, { ".-..",'l' }, 0);
    Tree::Insert(this->node, { "..-.",'f' }, 0);
    Tree::Insert(this->node, { "...-",'v' }, 0);
    Tree::Insert(this->node, { "....",'h' }, 0);

    return node;
}

void Tree::Check(std::string value, int i, char& res)
{
    Tree::Find(this->node, value, i, res);

}
