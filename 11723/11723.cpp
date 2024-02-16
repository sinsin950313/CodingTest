#include <iostream>
#include <set>
#include <string>

int Solve() {
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
    std::cout.tie(nullptr);

	int N;
	std::cin >> N;

	std::set<int> s, Temp;
    for (int i = 1; i <= 20; i++)
    {
        Temp.insert(i);
    }

    for (int i = 0; i < N; i++)
    {
        std::string Order;
        int Value;

		std::cin >> Order;
		if (Order == "add")
        {
			std::cin >> Value;
			s.insert(Value);
		}
		else if (Order == "check")
        {
            std::cin >> Value;
            if (s.find(Value) == s.end())
            {
                std::cout << "0" << '\n';
            }
            else 
            {
                std::cout << "1" << '\n';
            }
		}
		else if (Order == "remove")
        {
			std::cin >> Value;
			s.erase(Value);
		}
		else if (Order == "toggle")
        {
			std::cin >> Value;
			if (s.find(Value) == s.end())
            {
                s.insert(Value);
            }
			else 
            {
                s.erase(Value);
            }
		}
		else if (Order == "all")
        {
			s = Temp;
		}

		else if (Order == "empty")
        {
			s.clear();
        }

	}
	return 0;
}