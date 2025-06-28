import json

data = ''' {
    "store": {
        "name": "Tech Hub",
        "location": {
            "city": "San Francisco",
            "address": {
                "street": "123 Market St",
                "postalCode": "94103"
            }
        },
        "departments": [
            {
                "name": "Electronics",
                "products": [
                    {
                        "id": 201,
                        "name": "Laptop",
                        "brand": "BrandX",
                        "price": 999.99,
                        "specifications": {
                            "processor": "Intel i7",
                            "memory": "16GB",
                            "storage": "512GB SSD"
                        }
                    },
                    {
                        "id": 202,
                        "name": "Smartphone",
                        "brand": "BrandY",
                        "price": 799.99,
                        "specifications": {
                            "screenSize": "6.1 inches",
                            "battery": "4000mAh",
                            "camera": "12MP"
                        }
                    }
                ]
            },
            {
                "name": "Accessories",
                "products": [
                    {
                        "id": 301,
                        "name": "Wireless Mouse",
                        "brand": "BrandZ",
                        "price": 29.99,
                        "specifications": {
                            "batteryLife": "12 months",
                            "connectivity": "Bluetooth"
                        }
                    },
                    {
                        "id": 302,
                        "name": "Keyboard",
                        "brand": "BrandX",
                        "price": 49.99,
                        "specifications": {
                            "layout": "QWERTY",
                            "connectivity": "Wireless"
                        }
                    }
                ]
            }
        ]
    }
} '''

parsed_data = json.loads(data)

#1.1
name = parsed_data["store"]["name"]
city = parsed_data["store"]["location"]["city"]

print('Name of the store: ', name)
print('Located in ', city, ' city')

#1.2
departments = parsed_data["store"]["departments"]
for dept in departments:
    if(dept["name"] == "Electronics"):
        for product in dept['products']:
            print('Name: ', product["name"], " price is: ", product["price"])


#1.3
brand = parsed_data["store"]["departments"][1]["products"][0]["brand"]
specifications = parsed_data["store"]["departments"][1]["products"][0]["specifications"]
print('Brand name: ', brand)
for specs in specifications:
    print(specs,': ', specifications[specs] )

#1.4
smartphone = parsed_data["store"]["departments"][0]["products"][1]
smartphone["price"] = 749.99
data = json.dumps(parsed_data)
print(data)
