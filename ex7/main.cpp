#include <cstring>
#include <iostream>

using namespace std;

const int MAX_PRODUCTS_COUNT = 100;
const int MAX_ORDERS_COUNT = 100;

// TODO
class ProductsManager;
class OrdersManager;

/// TODO use something like: https://stackoverflow.com/questions/2978315/c-where-to-store-a-global-counter
int g_currentProductId = 1;
/// Ensure unique ids using this global value
///
/// Using such function adds flexibility, as the implementation
/// of the function may change in the future (the way uniqueness is
/// achieved).
int generateUniqueId()
{
    return g_currentProductId++;
}

// Escape normal string for something that
// is represented by a set of such strings
// N.B.! We may use enum class to avoid adding the enum
// values to the global space. This feature is present
// since c++11
//enum class OrderStatus {
enum OrderStatus {
    SHIPPED,
    WAITING,
    DELIVERED
};

/// Represents a customer's order in our shop
lass Order {
public:
    Order(int id, int productId, char* address)
        : m_id(id)
        , m_productId(productId)
    {

        //m_status = OrderStatus::WAITING;
        m_status = WAITING;

        // manage simple dynamic string
        m_address = new char[strlen(address) + 1];
        strcpy(m_address, address);
    }
    ~Order()
    {
        delete[] m_address;
    }

    // TODO
    char* getAddress() const;
    int getProductId() const;
    OrderStatus getStatus() const;

    // Go to next possible status
    void changeStatus();

private:
    int         m_id;
    char*       m_address;
    int         m_productId;
    OrderStatus m_status;
};

class Product {
public:
    Product(int id, char* name, double price, char* desciption)
        : m_id(id)
        , m_price(price)
    {
        // simply copy of the restricted in size name
        setName(name);

        // dynamic...
        setDescription(desciption);
    }
    ~Product()
    {
        delete[] m_description;
    }

    Product& operator=(const Product&); // TODO if needed

    /*
     * Mutators and selectors
     */
    int getId() const
    {
        return m_id;
    }

    double getPrice() const
    {
        return m_price;
    }

    void setPrice(double price)
    {
        m_price = price;
    }

    char* getName() const
    {
        return (char*)m_name;
    }
    void setName(char* name)
    {
        strcpy(m_name, name);
    }

    char* getDescription() const
    {
        return m_description;
    }
    void setDescription(char* description)
    {
        // Now lets see how we manage dynamic string
        // should be safe even if nullptr: https://stackoverflow.com/a/6731484
        delete[] m_description;
        // + 1 for the '\0' character
        m_description = new char[strlen(description) + 1];
        strcpy(m_description, description);
    }

private:
    /* data */
    int    m_id;
    double m_price;
    char   m_name[100];
    char*  m_description;
};

class BickieShop {
public:
    BickieShop()
    {
        // we start all clear
        m_productsCount = 0;
        m_ordersCount = 0;
    }

    ~BickieShop()
    {
        for (int i = 0; i < m_productsCount; ++i) {
            delete m_products[i];
        }
        for (int i = 0; i < m_ordersCount; ++i) {
            delete m_orders[i];
        }
    }

    /*****************
    *  Order utils  *
    *****************/
    void addOrder(int productId, char* address)
    {
        if (m_ordersCount < MAX_ORDERS_COUNT) {
            // construct a product using a generated unique identifier
            m_orders[m_ordersCount] = new Order(generateUniqueId(), productId, address);
            // Now increase the number of items
            m_ordersCount++;
        } else {
            cerr << "Now please sit down and breath slowly... We're full. We can't manage any more orders." << endl;
        }
    }

    void removeOrder(int orderId); // TODO

    /*******************
    *  Product utils  *
    *******************/
    Product* findProductById(int id)
    {
        for (int i = 0; i < m_productsCount; ++i) {
            if (m_products[i]->getId() == id) {
                return m_products[i];
            }
        }
        // possibly not
        return nullptr;
    }

    /// Create a product and add it to the existing list of such.
    /// NOTE: it generates an id for that item
    void addProduct(char* name, double price, char* desciption)
    {
        // XXX looks exactly like `addOrder`
        if (m_productsCount < MAX_PRODUCTS_COUNT) {
            // construct a product using a generated unique identifier
            m_products[m_productsCount] = new Product(generateUniqueId(), name, price, desciption);
            // Now increase the number of items
            m_productsCount++;
        } else {
            cerr << "Could not add any more products. Shop is full.";
        }
    }
    void editProduct(int productId, char* name, char* desc, double price);
    void removeProduct(int productId); // TODO

    /* View methods */
    // TODO we can improve the behaviour and allowed options for the use as much as we want

    // Notice how the View methods are restricted to do just simple operations, without much knowledge for
    // the surrounding class. They are responsible for i) showing information to the user and ii) getting
    // response from them. The *means* by which they succeed to accomplish that may be changed, e.g.
    // we may want to use some graphical interface of else. Having such separation allows us to change
    // only their implementation, avoiding changes to any other part of the system
    //
    // Last note: We are not creating any copies of the original objects

    void showIndexView()
    {
        cout << endl;
        cout << "Hello and prego! This is our small seduction shop where anyone can find their threats!" << endl;

        // TODO improve with more complex logic
        // Choose what to do:
        // - orders
        // - products list
        // - something else...
        showProductsListView(m_products, m_productsCount);
    }

    void showProductsListView(Product** products, int count)
    {
        cout << endl;
        cout << "Here's a list of our sinful chocolate enjoyments:" << endl;

        for (int i = 0; i < count; ++i) {
            cout << "<------>" << endl;
            cout << "Product id: " << products[i]->getId() << endl;
            cout << "Name: " << products[i]->getName() << endl;
            cout << "Price: " << products[i]->getPrice() << endl;
            /// Description is visible only from the detailed view
            cout << ">------<" << endl;
        }

        int answer;
        cout << "Do you what to buy anything? Choose a product to see details (by id). Use '0' for exit:" << endl;
        cin >> answer;

        // could be shortened to: !answer
        if (answer == 0) {
            cout << "Going back to main...";
            showIndexView();
        } else {
            // XXX could a product by the id be missing? What should we do?
            showProductDetailsView(findProductById(answer));
        }
    }

    void showProductDetailsView(Product* product)
    {
        cout << endl;
        cout << "======" << endl;
        cout << "===== " << product->getName() << " =====" << endl;
        cout << "Details : " << product->getDescription() << endl;
        cout << "Price: " << product->getPrice() << endl;

        char answer;
        cout << "Do you want to buy it (y/n)?" << endl;
        cin >> answer;

        // Some logic for the buying. Is this user intuitive?
        switch (answer) {
        case 'Y':
        case 'y':
            cout << "Going to order view..." << endl;
            showOrderView(product);
            break;
        case 'N':
        case 'n':
            cout << "Going back to main..." << endl;
            showIndexView();
        default:
            cout << "Bad option" << endl;
            showIndexView();
        }
    }

    void showOrderView(Product* product)
    {
        cout << endl;
        cout << "============ ============= ==============" << endl;
        cout << "You are about to buy: " << product->getName() << endl;
        cout << "Total price: " << product->getPrice() << endl;

        char buffer[200];

        cout << "Please enter your address:" << endl;
        /// Get rid of any extra characters: https://stackoverflow.com/a/1744756
        cin.ignore();
        cin.getline(buffer, 200, '\n');

        cout << "Great! We will contact you shortly to check you order. Thank you for choosing our shop!" << endl;
        addOrder(product->getId(), (char*)buffer);
        showIndexView();

        // How about...?
        /* cout << "Please enter your name:" << endl; */
        /* cin.getline(buffer, 200, '\n'); */
    }

    // Admin views
    void showEditProductView(Product& product); // TODO
    void showOrdersView(Order* orders);         // TODO

private:
    /* data */
    Product* m_products[MAX_PRODUCTS_COUNT];
    int      m_productsCount;

    Order*   m_orders[MAX_ORDERS_COUNT];
    int      m_ordersCount;
};

/// Remove item from the shop
///
/// Remove the product and ideally keep the array in proper state
void BickieShop::removeProduct(int productId)
{
    delete m_products[productId];

    for (int i = productId; i < m_productsCount - 1; ++i)
        m_products[i] = m_products[i + 1];
}

/// Edit a product by supplying a full list of properties
///
/// In case a proper value is given for a property, update it.
void BickieShop::editProduct(int id, char* name = nullptr, char* desc = nullptr, double price = -1)
{
    Product* product = findProductById(id);

    if (name) {
        product->setName(name);
    }

    if (desc) {
        product->setDescription(name);
    }

    if (price >= 0) {
        product->setPrice(price);
    }
}

int main()
{
    BickieShop shop;

    shop.addProduct((char*)"Some", 2.0, (char*)"The some of some.");
    shop.addProduct((char*)"Want Some", 10.0, (char*)"Quite expensive version of Some.");

    shop.showIndexView(); // this could be started with shop creation

    // it will allow changing to products list view
    // ... and the other view as well..

    return 0;
}

/* TODO s
  - Add accounts
    - how will it be integrated with the current system? Describe options and say why you've chosen the option you did.
    - an admin account will be able to:
        - [add|remove|edit]Product
        - update orders
            - edit order?
    - in case a user is registered, the orderView may be simpler (we could get the address from the user's info)
  - add validation where needed - sometimes validation is unnecessary as improper input is not possible
 */




