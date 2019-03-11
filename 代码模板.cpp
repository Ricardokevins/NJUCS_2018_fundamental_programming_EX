
    int equalstr(char*a, char *b)
{
	int flag(1);
	while (*a != '\0'&&*b != '\0')
	{
		if (*a != *b)
		{
			flag = 0;
			return flag;
		}
		a++;
		b++;
	}
	if (*a != *b)
	{
		flag = 0;
		return flag;
	}
	return flag;

}



int main() {
	char A[50];
	int x, y;
	char B[40] = "insert_at_beginning";
	char C[40] = "insert_at_ending";
	char D[40] = "insert_after";
	char E[40] = "delete";
	char F[40] = "print";
	char G[40] = "reverse_print";
	while (cin >> A) {
		if (equalstr(A, B)) {
			cin >> x;
			insert_at_beginning(x);
		}
		else if (equalstr(A, C)) {
			cin >> x;
			insert_at_ending(x);
		}
		else if (equalstr(A, D)) {
			cin >> x >> y;
			insert_after(x, y);
		}
		else if (equalstr(A, E)) {
			cin >> x;
			delete_node(x);
		}
		else if (equalstr(A, F)) {
			cin >> x;
			print(x);
		}
		else if (equalstr(A, G)) {
			cin >> x;
			reverse_print(head,x);
		}
	}
	return 0;
	，
}