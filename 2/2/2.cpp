#include <iostream>
#include <stack>
#include <vector>
#include <string>

using namespace std;

class MyStack
{
public:
	MyStack()
	{}
	~MyStack()
	{}

	void Push(int n, char s, int r, int c)
	{
		name.push(n);
		sym.push(s);
		row.push(r);
		col.push(c);
	}

	void Pop()
	{
		name.pop();
		sym.pop();
		row.pop();
		col.pop();
	}

	bool Empty()
	{
		return name.empty();
	}

	int Size()
	{
		return name.size();
	}

	stack <int> name;
	stack <char> sym;
	stack <int> row;
	stack <int> col;
};

class TextEditor
{
public:
	TextEditor();
	~TextEditor();

	void MoveCursorTo(int row, int col)
	{
		row = row;
		col = col;
	}

	void InsertChar(char c)
	{
		if (row == 10 && col == 10)
			return;

		if (row == 10)
		{
			row = 0;
			col++;
		}

		MoveCursorTo(row + 1, col);
		contain.Push(1, 'c', row, col);
		field[++row][col] = c;
	}

	void Delete()
	{
		MoveCursorTo(row, col);

		if (row == 0 && col == 0)
			return;

		field[row][col] = '0';

		if (row == 1 && col != 0)
		{
			row = 10;
			col--;
		}
		else
			row--;

		contain.Push(0, '0', row, col);
	}

	void Undo()
	{
		if (contain.Size() < 2)
			return;

		if (contain.name.top() == 1)
		{
			row = contain.row.top();
			col = contain.col.top();
			contain.Pop();
			Delete();
			contain.Pop();
		}

		if (contain.name.top() == 0)
		{
			row = contain.row.top();
			col = contain.col.top();
			char sym = contain.sym.top();
			contain.Pop();
			InsertChar(sym);
			contain.Pop();
		}
	}

	void Redo()
	{
		if (contain.Size() < 1)
			return;

		if (contain.name.top() == 0)
		{
			row = contain.row.top();
			col = contain.col.top();
			contain.Pop();
			Delete();
			contain.Pop();
		}

		if (contain.name.top() == 1)
		{
			row = contain.row.top();
			col = contain.col.top();
			char sym = contain.sym.top();
			contain.Pop();
			InsertChar(sym);
			contain.Pop();
		}

	}

	void PrintText()
	{
		for (int i = 0; i < 10; i++)
		{
			for (int j = 0; j < 10; j++)
			{
				cout << field[i][j] << " ";
			}
		}
		cout << endl;
	}

private:
	int row = 0;
	int col = 0;
	MyStack contain;
	char field[10][10]{ '0' };
	char ReturnChar(string str);
};

TextEditor::TextEditor()
{
}

TextEditor::~TextEditor()
{
}

char TextEditor::ReturnChar(string str)
{
	return str[0];
}

int main()
{
	TextEditor text;
	text.InsertChar('a');
	text.InsertChar('a');
	text.InsertChar('a');
	text.Undo();
	text.Undo();
	text.Redo();
	text.PrintText();
}