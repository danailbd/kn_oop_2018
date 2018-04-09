#include <cstring>
#include <iostream>

using namespace std;


const int MAX_PRODUCTS_COUNT = 100;
const int MAX_ORDERS = 100;


// Escape normal string for something that
// is represented by a set of such strings
enum OrderStatus {
    SHIPPED,
    WAITING,
    DELIVERED
};



class Order
{
public:
    Order (int id, char* adress, int productId);
    ~Order ();

    char*       getAdress() const;
    int         getProductId() const;
    OrderStatus getStatus() const;

    // TODO Do we need mutators (setters)?
        

private:
    int         m_id;
    char       *m_adress;
    int         m_productId;
    OrderStatus m_status;
};



class Product
{
public:
    Product (int id, char* name, double price, char* desciption);
    ~Product () {
        delete [] m_description;
    }

    Product& operator= (const Product&);

    /*
     * Mutators and selectors
     */
    double getPrice() const {
        return m_price;
    };
    double setPrice(double price) {
        m_price = price;
    };

    char* getName() const {
        return (char*)m_name;
    };
    void setName(char* name) {
        strcpy(m_name, name);
    };

    char* getDescription() const {
        return m_description;
    };
    void setDescription(char* description) {
        // Now lets see how we manage dynamic string
        delete [] m_description;
        // + 1 for the '\0' character
        m_description = new char[strlen(description) + 1];
        strcpy(m_description, description);
    };

private:
    /* data */

    int    m_id;
    double m_price;
    char   m_name[100];
    char*  m_description;
};


class BickieShop
{
public:
    // TODO do we need some other constructor?
    BickieShop () {
        // empty for now
        m_productsCount = 0;
    }
    ~BickieShop () {
        for (int i = 0; i < m_productsCount; ++i) {
            delete m_products[i];
        }
        for (int i = 0; i < m_ordersCount; ++i) {
            delete m_orders[i];
        }
    }

    void addProduct(const Product&);
    void addProduct(/* int id  Can we generate it dynamically?*/, char* name, double price, char* desciption);
    void removeProduct(int productId);
    void editProduct(int productId,  char* name, char* desc, double price);

    void order(int productId, char *address, char *firstName, char *lastName) {
        // TODO
        // m_orders[orderCount] = new Order();
    }

    // S - Single responsibility
    // O - Open-close


    void listProducts() const; // TODO
    void showProductDetails() const; // TODO

private:
    Product& getProduct(int id);
    
    /* data */
    Product *m_products[MAX_PRODUCTS_COUNT];
    int      m_productsCount;

    Order   *m_orders[MAX_ORDERS];
    int      m_ordersCount;
};


/// Add product to the shop using copy constructor
///
/// As we don't to use a default contructor for our products,
/// we create them using dynamic memory.
void BickieShop::addProduct(const Product& p) {
    if (m_productsCount < MAX_PRODUCTS_COUNT) {
        m_products[m_productsCount] = new Product(p);
        ++m_productsCount;
    }
    else std::cerr << "Max Products Count exceeded!";
}

/// Remove item from the shop
///
/// Remove the product and ideally keep the array in proper state
void BickieShop::removeProduct (int productId) {
    delete m_products[productId];

    for (int i = productId; i < m_productsCount - 1; ++i)
        m_products[i] = m_products[i + 1];
}


/// Edit a product by supplying a full list of properties
///
/// In case a proper value is given for a property, update it.
void BickieShop::editProduct(int id, char* name = nullptr, char* desc = nullptr, double price = -1) {
    Product& product = m_products[getElementIdxById(id)];

    if (name) {
        product.setName(name);
    }

    if (desc) {
        product.setDescription(name);
    }

    if (price >= 0) {
        product.setPrice(price);
    }
}



int main()
{
    BickieShop shop();

    shop.addProduct(...);

    shop.listProducts();
    shop.editProduct(1, nullptr, "gfsgdfgd");

    return 0;
}
