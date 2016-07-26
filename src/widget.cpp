//=======================
//main rect values class:

#include "stdafx.h"
#include "widget.h"

bool widget::operator==(const widget A)
{
return	Position.top == A.Position.top &&
		Position.bottom == A.Position.bottom &&
		Position.left == A.Position.right &&
		Position.right == A.Position.right &&

		father == A.father &&
		ID == A.ID &&
		type == A.type;
}

bool widget::operator!=(const widget A)
{
	return !(*this == A);
}

widget::widget()
{
	Position.bottom = 0;
	Position.left = 0;
	Position.right = 0;
	Position.top = 0;

	Tab_validation = false;
	width = 0;
	height = 0;
	valid = 0;
	type.clear();
	ID.clear();
}

void widget::Set_position(int x, int y, int h, int w)
{
	height = h;
	width = w;
	Position.top = x;
	if(!drop_list)			
		Position.bottom = x + height;
	else
		Position.bottom = x + drop_list_height;		//drop_list resize
	Position.left = y;
	Position.right = y + width;
}

//takes a pointer to a widget and makes it the father of the current object
void widget::Change_father(widget* obj)
{
	//delete child from father's child list
	if (this->father != NULL)
	{
		for (int i = 0; i < this->father->child.size(); i++)
		{
			if (this->father->child[i] == this)
			{
				//delete the element
				this->father->child.erase(this->father->child.begin() + i, this->father->child.begin() + i + 1);
				break;
			}
		}
	}

	//this father is obj
	this->father = obj;

	//father has the child "this"
	this->father->child.push_back(this);
}

//returns true if the current object has a father
bool widget::Has_father()
{
	return this->father != NULL;
}

//returns a copy of the father of the current widget
widget widget::Get_father() const
{
	return *(this->father);
}

//returns a pointer to the father of the current widget
widget* widget::Get_father_pointer() const
{
	return this->father;
}

//returns the number of children a widget has
size_t widget::Get_nr_children() 
{ 
	return this->child.size(); 
}

//returns a vector of pointers to the children of the current widget
vector<widget*> widget::get_pointers_to_children() const
{
	return this->child;
}

//changes the list of pointers to children of the current object
void widget::change_pointers_to_children(const vector<widget*> &new_Children) 
{
	child = new_Children;
}

void widget::Set_drop_list()
{
	drop_list = true;
}

bool widget::Is_drop_list() const
{
	return drop_list;
}

bool widget::Is_checkbox() const
{
	return checkbox;
}

bool widget::Is_browse_button() const
{
	return	(type == L"PUSHBUTTON") &&
			(name == L"..." ||
			(Position.bottom - Position.top <= 10 || Position.right - Position.left <= 10));
}

bool widget::contains_mid_of(const widget &obj) const
{
	int mid_x = (obj.Get_left() + obj.Get_right()) / 2;
	int mid_y = (obj.Get_top() + obj.Get_bottom()) / 2;

	return	(mid_x <= Position.right && mid_x >= Position.left &&
			mid_y <= Position.bottom && mid_y >= Position.top);
}

