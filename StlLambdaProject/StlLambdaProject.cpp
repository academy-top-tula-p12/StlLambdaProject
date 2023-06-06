#include <iostream>
#include <functional>

template <typename T1, typename T2>
auto sum(T1 a, T2 b) 
{ 
    return a + b; 
}

void repeat(int count, std::function<void(int)> f)
{
    for (int i = 0; i < count; i++)
        f(i);
}

int main()
{
    std::string hi = "Hello";
    int x = 1;
    int y = 2;

    auto func = [&](auto& name)
    {
        std::cout << hi << " " << x << y << "\n";
        hi = "Good by";
        x = 100;
        y = 200;
    };

    func("Bob");
    int n = 1;
    func(n);

    std::cout << typeid(func).name() << "\n";

    auto suml = [](auto a, auto b) { return a + b; };
    
    std::function<int(int, int)> sumlf {
        [](auto a, auto b)
        { return a + b;
        }
    };

    std::cout << suml(23, 78.6) << "\n";
    std::cout << suml(true, 'A') << "\n";

    std::cout << sumlf(23, 78.6) << "\n";
    std::cout << sumlf(true, 'A') << "\n";

    repeat(5, [](int n) {std::cout << n << "\n"; });

    auto l1 = [](auto a) { return a; };

    auto lcreate = [](auto a) 
    {
        class Counter 
        {
            int n;
        public:
            Counter(int n) : n{ n } {}
            int operator()() { return n++; }
        };
        return Counter(a);
    };
    std::cout << "\n";
    
    auto c1 = lcreate(4);
    for(int i = 0; i < 5; i++)
        std::cout << c1() << "\n";
    
    std::cout << "\n";

    auto c2 = lcreate(8);
    for (int i = 0; i < 5; i++)
        std::cout << c2() << "\n";

    std::cout << "\n";

    auto createCounter = [](auto count) {
        return [&]() { return count++; };
    };

    auto cf1 = createCounter(10);
    for (int i = 0; i < 5; i++)
        std::cout << cf1() << "\n";

    auto cf2 = createCounter(20);
    for (int i = 0; i < 5; i++)
        std::cout << cf2() << "\n";

    auto createAccum = [](auto start) {
        return [&](auto next) {
            start += next;
            return start;
        };
    };

    std::cout << "\n\n";

    auto ac1 = createAccum(0);
    std::cout << ac1(5) << "\n";
    std::cout << ac1(7) << "\n";
    std::cout << ac1(11) << "\n";

    auto ac2 = createAccum(100);
    std::cout << ac2(5) << "\n";
    std::cout << ac2(7) << "\n";
    std::cout << ac2(11) << "\n";

    auto createSumOnce = []() {
        bool isExec = false;
        return [=](auto a, auto b) mutable
        { 
            if (!isExec)
            {
                std::cout << a + b << "\n";
                isExec = true;
            }
            else
                std::cout << "only once!\n";
            
        };
    };
    
    auto sum1 = createSumOnce();

    sum1(10, 20);
    sum1(20, 30);
}
