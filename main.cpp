#include <iostream>
#include <vector>
#include <string>
#include <algorithm> // For reverse
#include <cmath>     // For sqrt
using namespace std;

// Function to compare two big integers correctly
int compareBigInt(vector<long long> x, vector<long long> y)
{
    if (x.size() > y.size())
        return 1; // x is greater
    if (x.size() < y.size())
        return -1; // y is greater
    for (int i = 0; i < x.size(); i++)
    {
        if (x[i] > y[i])
            return 1;
        if (x[i] < y[i])
            return -1;
    }
    return 0; // Equal
}

// Function to add two big integers
vector<long long> add(vector<long long> x, vector<long long> y)
{
    reverse(x.begin(), x.end());
    reverse(y.begin(), y.end());

    vector<long long> ans;
    long long carry = 0;
    long long len = min(x.size(), y.size());

    for (int i = 0; i < len; i++)
    {
        long long val = x[i] + y[i] + carry;
        carry = val / 10;
        ans.push_back(val % 10);
    }

    for (int i = len; i < x.size(); i++)
    {
        long long val = x[i] + carry;
        carry = val / 10;
        ans.push_back(val % 10);
    }

    for (int i = len; i < y.size(); i++)
    {
        long long val = y[i] + carry;
        carry = val / 10;
        ans.push_back(val % 10);
    }

    while (carry)
    {
        ans.push_back(carry % 10);
        carry /= 10;
    }

    reverse(ans.begin(), ans.end());
    return ans;
}

// Function to subtract two big integers (x - y)
vector<long long> subtract(vector<long long> x, vector<long long> y)
{
    if (compareBigInt(x, y) < 0)
        swap(x, y); // Ensure x >= y

    reverse(x.begin(), x.end());
    reverse(y.begin(), y.end());

    vector<long long> ans;
    long long borrow = 0;

    for (int i = 0; i < y.size(); i++)
    {
        long long val = x[i] - y[i] - borrow;
        if (val < 0)
        {
            val += 10;
            borrow = 1;
        }
        else
        {
            borrow = 0;
        }
        ans.push_back(val);
    }

    for (int i = y.size(); i < x.size(); i++)
    {
        long long val = x[i] - borrow;
        if (val < 0)
        {
            val += 10;
            borrow = 1;
        }
        else
        {
            borrow = 0;
        }
        ans.push_back(val);
    }

    while (ans.size() > 1 && ans.back() == 0)
        ans.pop_back();

    reverse(ans.begin(), ans.end());
    return ans;
}

// Function to multiply two big integers
vector<long long> multiply(vector<long long> x, vector<long long> y)
{
    int n = x.size(), m = y.size();
    vector<long long> ans(n + m, 0);

    reverse(x.begin(), x.end());
    reverse(y.begin(), y.end());

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            ans[i + j] += x[i] * y[j];
            if (ans[i + j] >= 10)
            {
                ans[i + j + 1] += ans[i + j] / 10;
                ans[i + j] %= 10;
            }
        }
    }

    while (ans.size() > 1 && ans.back() == 0)
        ans.pop_back();

    reverse(ans.begin(), ans.end());
    return ans;
}

// Function to divide two big integers (x / y) and return quotient
vector<long long> divide(vector<long long> x, vector<long long> y)
{
    if (compareBigInt(x, y) < 0)
        return {0}; // If x < y, quotient is 0

    vector<long long> quotient;
    vector<long long> remainder;

    for (size_t i = 0; i < x.size(); i++)
    {
        remainder.push_back(x[i]);

        while (remainder.size() > 1 && remainder[0] == 0)
            remainder.erase(remainder.begin()); // Remove leading zeros

        vector<long long> temp = remainder;
        int count = 0;

        while (compareBigInt(temp, y) >= 0)
        {
            temp = subtract(temp, y);
            count++;
        }

        quotient.push_back(count);
        remainder = temp;
    }

    while (quotient.size() > 1 && quotient[0] == 0)
        quotient.erase(quotient.begin()); // Remove leading zeros

    return quotient;
}

// Function to find modulus (x % y)
long long mod(vector<long long> x, long long y)
{
    long long remainder = 0;
    for (long long digit : x)
    {
        remainder = (remainder * 10 + digit) % y;
    }
    return remainder;
}

// Function to exponentiate (big integer ^ power)
vector<long long> power(vector<long long> x, long long exponent)
{
    vector<long long> ans = {1};
    for (long long i = 0; i < exponent; i++)
    {
        ans = multiply(ans, x);
    }
    return ans;
}

// Function to find the square root of a big integer
long long sqrtBigInt(vector<long long> x)
{
    string num = "";
    for (auto d : x)
        num += (d + '0');
    long long val = stoll(num);
    return sqrt(val);
}

// Function to find the number of digits in a big integer
int countDigits(vector<long long> x)
{
    return x.size();
}


// Function to calculate factorial
vector<long long> factorial(long long n) {
    vector<long long> result = {1};
    for (long long i = 2; i <= n; i++) {
        vector<long long> temp;
        long long int num = i;
        while (num > 0) {
            temp.insert(temp.begin(), num % 10);
            num /= 10;
        }
        result = multiply(result, temp);
    }
    return result;
}

// Function to find Fibonacci of a big integer
vector<long long> fibonacci(long long n) {
    if (n == 0)
        return {0};
    if (n == 1)
        return {1};

    vector<long long> a = {0}, b = {1}, c;
    for (long long i = 2; i <= n; i++) {
        c = add(a, b);
        a = b;
        b = c;
    }

    return b;
}

// Function to compute Catalan number
vector<long long> catalan(long long n) {
    vector<long long> x = factorial(2 * n);
    vector<long long> y1 = factorial(n + 1);
    vector<long long> y2 = factorial(n);

    // Multiply the denominators
    vector<long long> y = multiply(y1, y2);

    // Perform division (num / denom)
    return divide(x, y);
}

// Function to print a big integer
void printBigInt(vector<long long> x)
{
    for (long long num : x)
        cout << num;
    cout << endl;
}

// Main function
int main()
{

    long long t;
    cin >> t;

    while (t--)
    {
        string a, b;
        cin >> a >> b;

        vector<long long> s, d;

        for (char ch : a)
            s.push_back(ch - '0');
        for (char ch : b)
            d.push_back(ch - '0');

        vector<long long> sum = add(s, d);
        vector<long long> diff = subtract(s, d);
        vector<long long> prod = multiply(s, d);
        vector<long long> quotient = divide(s, d);
        long long modRes = mod(s, stoll(b));
        vector<long long> powerRes = power(s, 2);
        long long sqrtRes = sqrtBigInt(s);
        int digits = countDigits(s);

        cout << "Sum: ";
        printBigInt(sum);
        cout << "Difference: ";
        printBigInt(diff);
        cout << "Product: ";
        printBigInt(prod);
        cout << "Quotient: ";
        printBigInt(quotient);
        cout << "Modulo: " << modRes << endl;
        cout << "Power (Square): ";
        printBigInt(powerRes);
        cout << "Square Root: " << sqrtRes << endl;
        cout << "Number of Digits: " << digits << endl;
        
        long long n = stoll(a);
        cin>>n;
        cout << "Factorial: ";
        printBigInt(factorial(n));
        cout << "Fibonacci: ";
        printBigInt(fibonacci(n));
        cout << "Catalan Number: ";
        printBigInt(catalan(n));

        compareBigInt(s, d);
    }

    return 0;
}
