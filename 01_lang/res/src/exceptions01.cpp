#include <iostream>
#include <exception>

#define func_start() (std::cout << __func__ << " starts\n")
#define func_end() (std::cout << __func__ << " ends\n")

class ExceptionBase
{
public:
    virtual const char *What() const
    {
        return "ExceptionBase.What()";
    }
};

class MathException : public ExceptionBase
{
public:
    virtual const char *What() const override
    {
        return "MathException.What()";
    }
};

class DivideByZeroError : public MathException
{
public:
    virtual const char *What() const override
    {
        return "DivideByZeroError.What()";
    }
};

void custom_abort()
{
    func_start();
    std::exit(EXIT_FAILURE);
    func_end();
}

class FileError
{
};

class FileReadError : public FileError
{
public:
    int get_line_number() const;
    const char *get_file_name() const;
};

class FileWriteError : public FileError
{
};



int main(int argc, char const *argv[])
{
    auto f = std::set_terminate(custom_abort);
    func_start();

    try
    {
        throw MathException{};
    }
    catch (DivideByZeroError &e)
    {
        std::cout << "Exception caught... e.What() -> " << e.What() << '\n';
    }
    catch (MathException &e)
    {
        std::cout << "Exception caught... e.What() -> " << e.What() << '\n';
    }
    catch (ExceptionBase &e)
    {
        std::cout << "Exception caught... e.What() -> " << e.What() << '\n';
    }
    catch (...)
    {
        // catch all
    }

    func_end();
}
