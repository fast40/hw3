#include <iostream>
#include <cassert>
#include "stack.h"

int main(int argc, char* argv[])
{
        Stack<int> stack;

        assert(stack.empty());

        stack.push(3);
        stack.push(2);
        stack.push(1);

        assert(stack.size() == 3);
        assert(stack.top() == 1);

        stack.pop();

        assert(stack.size() == 2);
        assert(stack.top() == 2);

        stack.pop();

        assert(stack.size() == 1);
        assert(stack.top() == 3);

        stack.pop();

        assert(stack.empty());
        assert(stack.size() == 0);

        bool errored_correctly = false;

        try {
                stack.top();
        }
        catch (std::underflow_error& e) {
                errored_correctly = true;
        }

        assert(errored_correctly);

        std::cout << "All tests passing" << std::endl;

        return 0;
}
