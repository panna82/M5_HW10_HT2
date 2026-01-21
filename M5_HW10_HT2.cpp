#include <iostream>
#include <vector>

class BigInteger
{
private:
	std::string bigInteger_;
	std::vector<int> bigIntegerTemp_{};
	std::string bigIntegerResult_;

	int base_ = 10;
	size_t size_ = 0;


public:
	BigInteger(const std::string& value) : bigInteger_{ value }, size_{ value.size() } {};

	BigInteger(const BigInteger& other) : bigInteger_{ other.bigInteger_ }, bigIntegerTemp_{ other.bigIntegerTemp_ }, size_{ other.size_ } {};

	BigInteger& operator=(const BigInteger& other)
	{
		if (this != &other)
		{
			bigInteger_ = other.bigInteger_;
			bigIntegerTemp_ = other.bigIntegerTemp_;
			size_ = other.size_;
		}
		return *this;
	};

	BigInteger(BigInteger&& other) noexcept : bigInteger_{ std::move(other.bigInteger_) }, bigIntegerTemp_{ std::move(other.bigIntegerTemp_) }, size_{ std::move(other.size_) }
	{
		other.bigIntegerTemp_.clear();
		other.bigInteger_.clear();
		other.size_ = 0;
	};

	BigInteger& operator=(BigInteger&& other) noexcept
	{
		if (this != &other)
		{
			bigInteger_ = std::move(other.bigInteger_);
			bigIntegerTemp_ = std::move(other.bigIntegerTemp_);
			size_ = other.size_;
			other.size_ = 0;
		}
		return *this;
	};

	std::string operator+(BigInteger& other)
	{
		bigIntegerResult_.clear();
		other.bigIntegerResult_.clear();
		bigIntegerResult_ = bigInteger_;
		other.bigIntegerResult_ = other.bigInteger_;

		if ((bigIntegerResult_[0] == '0' && bigIntegerResult_.size() == 1) && (other.bigIntegerResult_[0] == '0' && other.bigIntegerResult_.size() == 1))
			return bigIntegerResult_;

		int deltaSize = std::abs((static_cast<int>(size_) - static_cast<int>(other.size_)));

		if (size_ > other.size_)
		{
			other.size_ = size_;
			auto it = other.bigIntegerResult_.begin();
			for (int i = 0; i < deltaSize; i++)
			{
				other.bigIntegerResult_.insert(it, '0');
			}
		}
		else if (size_ < other.size_)
		{
			size_ = other.size_;
			auto it = bigIntegerResult_.begin();
			for (int i = 0; i < deltaSize; i++)
			{
				bigIntegerResult_.insert(it, '0');
			}
		}

		bigIntegerTemp_.clear();
		bigIntegerTemp_.reserve(size_ + 1);
		other.bigIntegerTemp_.reserve(size_ + 1);

		int j = static_cast<int>(size_);
		int h = 0;

		for (--j; j >= 0; --j, h++)
		{
			bigIntegerTemp_.push_back((bigIntegerResult_[j] - '0') + (other.bigIntegerResult_[j] - '0'));
			if (bigIntegerTemp_[h] < 0)
				bigIntegerTemp_[h] = 0;
		}
		if (bigIntegerTemp_[static_cast<int>(size_) - static_cast<int>(1)] >= 9)
		{
			j = static_cast<int>(size_) + 1;
			bigIntegerTemp_.push_back(0);
		}
		else
		{
			j = static_cast<int>(size_);
		}

		for (size_t i = 0; i < size_; i++)
		{
			if (bigIntegerTemp_[i] >= base_)
			{
				bigIntegerTemp_[i + 1] += bigIntegerTemp_[i] / base_;
				bigIntegerTemp_[i] %= base_;
			}
		}

		bigIntegerResult_.clear();

		for (--j; j >= 0; --j)
		{
			char k = bigIntegerTemp_[j] + '0';
			bigIntegerResult_.push_back(k);
		}

		return bigIntegerResult_;
	};

	std::string operator*(BigInteger& other)
	{
		bigIntegerResult_.clear();
		other.bigIntegerResult_.clear();
		bigIntegerTemp_.clear();

		bigIntegerResult_ = bigInteger_;
		other.bigIntegerResult_ = other.bigInteger_;


		if ((bigIntegerResult_[0] == '0' && bigIntegerResult_.size() == 1) || (other.bigIntegerResult_[0] == '0' && other.bigIntegerResult_.size() == 1))
			return bigIntegerResult_ = '0';

		bigIntegerTemp_.clear();

		int max_size = bigIntegerResult_.size() + other.bigIntegerResult_.size();

		BigInteger::bigIntegerTemp_.resize(max_size, 0);

		for (int i = bigIntegerResult_.size() - 1; i >= 0; --i)
		{
			for (int j = other.bigIntegerResult_.size() - 1; j >= 0; --j)
				bigIntegerTemp_[max_size - 2 - i - j] += (bigIntegerResult_[i] - '0') * (other.bigIntegerResult_[j] - '0');
		}

		for (size_t i = 0; i < bigIntegerTemp_.size() - 1; i++)
		{
			bigIntegerTemp_[i + 1] += bigIntegerTemp_[i] / base_;
			bigIntegerTemp_[i] %= base_;
		}

		while (bigIntegerTemp_.back() == 0)
		{
			bigIntegerTemp_.pop_back();
		}

		std::reverse(bigIntegerTemp_.begin(), bigIntegerTemp_.end());

		bigIntegerResult_.clear();

		for (auto i : bigIntegerTemp_)
		{
			char k = i + '0';
			bigIntegerResult_.push_back(k);
		}
		return bigIntegerResult_;
	}

	~BigInteger() {};
};

int main() {

	auto number1 = BigInteger("114575");
	auto number2 = BigInteger("78524");
	auto result = number1 + number2;
	std::cout << result;
	return 0;
}
