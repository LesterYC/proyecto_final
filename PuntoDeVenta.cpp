#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <vector>

using namespace std;

void compraProductos();
void consultarInventario();
void busquedaProductos();
void eliminacionProductos();
void registrarVentas();

//OBJETOS
struct Producto {
    int id;
    string nombre;
    double precioCompra, precioVenta;
    int cantidad;
};

struct ProductoVenta {
    string nombre;
    int idProductoVenta, cantidad;
    float precioVenta;
};

struct Venta {
    vector<ProductoVenta> productos;
    float total;
    string metodoPago;
};

struct Vendedor {
    int idVendedor;
    string nombreVendedor, direccionVendedor, telefonoVendedor;
};

struct Cliente {
    string nombreCliente, direccionCliente, telefonoCliente, fechaVenta;
};

//VARIABLES GLOBALES
int idProducto=0, cantidad=0, idBusqueda = 0, contador = 0, seleccionMenu = 0, seleccionMetodoPago = 0;
float precioCompra=0, precioVenta=0;
string nombreProducto, nombreMetodoPago, nombreBusqueda;
char continuar = 's';
Producto productos[100];

//FUNCIONES
void compraProductos(){
    string archivo = "inventario_punto_venta.txt";
    ifstream archivoEntrada(archivo);

    if (archivoEntrada.good()) {
        consultarInventario();
        ifstream archivo("inventario_punto_venta.txt");
        if (archivo.is_open()) {
            while (archivo >> idProducto >> nombreProducto >> precioCompra >> precioVenta >> cantidad && contador < 100) {
                productos[contador] = { idProducto, nombreProducto, precioCompra, precioVenta, cantidad };
                contador++;
            }
            archivo.close();
        } else {
            cout << "No se pudo abrir el archivo" << endl;
        }
        cout << "Ingrese codigo del producto: ";
        cin >> idBusqueda;
        for (int i = 0; i < contador; i++) {
            if(productos[i].id == idBusqueda){
                int idtemporal = productos[i].id, cantidadTemporal = 0;
                ifstream acceder("inventario_punto_venta.txt");
                ofstream modificar("inventario_punto_venta_modificado.txt");
                while (!acceder.eof()) {
                    acceder >> idProducto >> nombreProducto >> precioCompra >> precioVenta >> cantidad;
                    if (idProducto == idtemporal && !acceder.eof()){
                        cout << "Nombre del producto: " << nombreProducto << endl;
                        cout << "Cantidad actual: " << cantidad << endl;
                        cout << "Actualice la cantidad: ";
                        cin >> cantidadTemporal;
                        cantidadTemporal = cantidad+cantidadTemporal;

                        modificar << idProducto << " " << nombreProducto << " " << precioCompra << " " << precioVenta << " " << cantidadTemporal << endl;
                    }else{
                        if (!acceder.eof()){
                            modificar << idProducto << " " << nombreProducto << " " << precioCompra << " " << precioVenta << " " << cantidad << endl;
                        }
                    }
                }
                acceder.close();
                modificar.close();
                remove("inventario_punto_venta.txt");
                rename("inventario_punto_venta_modificado.txt", "inventario_punto_venta.txt");
                return;
            }
        }

        for (int i = 0; i < contador; i++) {
            if(productos[i].id != idBusqueda){
                cout << "Ingrese nombre del producto: ";
                cin >> nombreProducto;
                cout << "Ingrese precio de compra del producto: ";
                cin >> precioCompra;
                cout << "Ingrese precio de venta del producto: ";
                cin >> precioVenta;
                cout << "Ingrese numero de cantidad: ";
                cin >> cantidad;
                ofstream creacion("inventario_punto_venta.txt", ios::app);
                creacion << idBusqueda << " " << nombreProducto << " " <<precioCompra << " " <<precioVenta << " " << cantidad << endl;
                creacion.close();
                return;
            }
        }
    } else {
        cout << "El archivo " << archivo << " no existe, creando archivo..." << endl;
        ofstream archivoSalida(archivo);
        archivoSalida.close();
        cout << "Archivo creado exitosamente." << endl;
        system("pause");
    }
}

void consultarInventario(){
    system("cls");
    ifstream lectura("inventario_punto_venta.txt");
    while (!lectura.eof()) {
        lectura >> idProducto >> nombreProducto >> precioCompra >> precioVenta >> cantidad;
        if (!lectura.eof() ){
            if (cantidad>0)
            {
                cout << endl<< "##################################" << endl;
                cout << "Codigo del producto: " << idProducto<<endl;
                cout << "Nombre del producto: " << nombreProducto << endl;
                cout << "Precio de compra: " << precioCompra<<endl;
                cout << "Precio de venta: " << precioVenta << endl;
                cout << "Cantidad: " << cantidad;
                cout << endl<< "##################################" << endl;
            }
            else
            {
                cout << endl<< "##################################" << endl;
                cout << "# PRODUCTO AGOTADO, PROXIMAMENTE #";
                cout << endl<< "##################################" << endl;
            }
            
        }
    }
    lectura.close();
}

void busquedaProductos(){
    system("cls");
    cout << "Ingrese el codigo del producto: ";
    cin >> idBusqueda;
    cout << "Ingrese el nombre del producto: ";
    cin >> nombreBusqueda;
    ifstream acceder("inventario_punto_venta.txt");
    while (!acceder.eof()) {
        acceder >> idProducto>>nombreProducto>>precioCompra>>precioVenta>>cantidad;
        if((idProducto == idBusqueda && nombreProducto == nombreBusqueda) && !acceder.eof()){
            cout << endl<<"##################################" << endl;
            cout << "           RESULTADO";
            cout << endl<<"##################################" << endl;
            cout << "Codigo del producto: " << idProducto<<endl;
            cout << "Nombre del producto: " << nombreProducto << endl;
            cout << "Precio de compra: " << precioCompra<<endl;
            cout << "Precio de venta: " << precioVenta << endl;
            cout << "Cantidad: " << cantidad << endl;
            cout << "##################################" << endl;
            return;
        } else if((idProducto != idBusqueda || nombreProducto != nombreBusqueda) && !acceder.eof()){
            cout << endl<<"##################################" << endl;
            cout << "           NO SE ENCONTRO";
            cout << endl<<"##################################" << endl;
            return;
        }       
    }
    acceder.close();
    system("pause");
}

void eliminacionProductos(){
    system("cls");
    consultarInventario();
    cout << "Ingrese el Codigo del producto a eliminar: ";
    cin >> idBusqueda;
    ifstream acceder("inventario_punto_venta.txt");
    ofstream modificar("inventario_punto_venta_modificado.txt");
    while (!acceder.eof()) {
        acceder >> idProducto >> nombreProducto >> precioCompra >> precioVenta >> cantidad;
        if (idProducto == idBusqueda && !acceder.eof()){
            cout << endl << "El id:" << idBusqueda << " ha sido eliminado" << endl;        
        }else{
            if (!acceder.eof()){
                modificar << idProducto << " " << nombreProducto << " " << precioCompra << " " << precioVenta << " " << cantidad << endl;
            }
        }
    }
    acceder.close();
    modificar.close();
    remove("inventario_punto_venta.txt");
    rename("inventario_punto_venta_modificado.txt", "inventario_punto_venta.txt");
    system("pause");
}

void registrarVentas(){
    system("cls");
    Vendedor vendedor;
    Cliente cliente;
    vector<Venta> ventas;
    char continuarVenta = 's';
    cout << "####################" << endl;
    cout << " Datos del vendedor " << endl;
    cout << "####################" << endl;
    cout << "Ingrese el nombre: ";
    cin >> vendedor.nombreVendedor;
    cout << "Ingrese la direccion: ";
    cin >> vendedor.direccionVendedor;
    cout << "Ingrese el telefono: ";
    cin >> vendedor.telefonoVendedor;
    cout << "Ingrese el ID: ";
    cin >> vendedor.idVendedor;

    cout << endl << "###################" << endl;
    cout << " Datos del cliente " << endl;
    cout << "###################" << endl;
    cout << "Ingrese el nombre: ";
    cin >> cliente.nombreCliente;
    cout << "Ingrese la direccion: ";
    cin >> cliente.direccionCliente;
    cout << "Ingrese el telefono: ";
    cin >> cliente.telefonoCliente;
    cout << "Ingrese la fecha: ";
    cin >> cliente.fechaVenta;
    
    while (continuarVenta == 's') {
        Venta venta;
        char agregar_producto = 's';
        
        while (agregar_producto == 's') {
            ProductoVenta producto;
            consultarInventario();
            cout << endl << "##################" << endl;
            cout << " Datos de Produto " << endl;
            cout << "##################" << endl;
            cout << "Ingrese el codigo del producto a vender: ";
            cin >> producto.idProductoVenta;
            cout << "Ingrese el cantidad del producto a vender: ";
            cin >> producto.cantidad;
            
            ifstream acceder("inventario_punto_venta.txt");
            ofstream modificar("inventario_punto_venta_modificado.txt");
            while (!acceder.eof()) {
                acceder >> idProducto >> nombreProducto >> precioCompra >> precioVenta >> cantidad;
                if (idProducto == producto.idProductoVenta && !acceder.eof()){
                    cantidad = cantidad - producto.cantidad;
                    producto.nombre = nombreProducto;
                    producto.precioVenta = precioVenta;
                    modificar << idProducto << " " << nombreProducto << " " << precioCompra << " " << precioVenta << " " << cantidad << endl;
                }else{
                    if (!acceder.eof()){
                        modificar << idProducto << " " << nombreProducto << " " << precioCompra << " " << precioVenta << " " << cantidad << endl;
                    }
                }
            }
            acceder.close();
            modificar.close();
            remove("inventario_punto_venta.txt");
            rename("inventario_punto_venta_modificado.txt", "inventario_punto_venta.txt");

            venta.productos.push_back(producto);
            
            cout << "Desea agregar otro producto? (s/n): ";
            cin >> agregar_producto;
        }

        float total_venta = 0;
        for (int i = 0; i < venta.productos.size(); i++) {
            venta.productos[i].precioVenta = venta.productos[i].precioVenta * venta.productos[i].cantidad;
            total_venta += venta.productos[i].precioVenta;
        }
        do{
            system("cls");
            cout << "################" << endl;
            cout << " METODO DE PAGO " << endl;
            cout << "################" << endl;
            cout << "1. Tarjeta" << endl;
            cout << "2. Efectivo" << endl;
            cout << "################" << endl;
            cout << "Ingrese el metodo de pago: ";
            cin >> seleccionMetodoPago;
            switch (seleccionMetodoPago){
            case 1: nombreMetodoPago = "Tarjeta"; break;
            case 2: nombreMetodoPago = "Efectivo"; break;
            default: cout << "Opcion no valida." << endl; break;
        }
        } while (seleccionMetodoPago > 2);
        venta.total = total_venta;
        venta.metodoPago = nombreMetodoPago;
        ventas.push_back(venta);
        cout << "Desea registrar otra venta? (s/n): ";
        cin >> continuarVenta;
    }

    // IMPRESION RECIBO
    system("cls");
    cout << "################################" << endl;
    cout << "FACTURA" << endl;
    cout << "EL PUNTO DE VENTA FELIZ" << endl;
    cout << "Fecha de Factura" << endl << cliente.fechaVenta << endl;
    cout << "-----------------" << endl;
    cout << "Servido por: " << vendedor.nombreVendedor << endl << endl;
    cout << "Nombre Cliente: " << cliente.nombreCliente << endl;
    cout << "Dirección Cliente: " << cliente.direccionCliente << endl;
    cout << "Teléfono Cliente: " << cliente.telefonoCliente << endl << endl;
    for (int i = 0; i < ventas.size(); i++) {
        cout << "Venta #" << i+1 << ":" << endl;
        for (int j = 0; j < ventas[i].productos.size(); j++) {
            cout << ventas[i].productos[j].nombre << " - " << ventas[i].productos[j].cantidad << " - " << ventas[i].productos[j].precioVenta << endl;
        }
        cout << "-----------------" << endl;
        cout << "Total: " << ventas[i].total << endl;
        cout << "Metodo de Pago: " << ventas[i].metodoPago << endl << endl;
    }
    cout << "Visitanos en: " << vendedor.direccionVendedor << endl;
    cout << "################################" << endl;


    string nombreArchivo = "ventas_";
    int numeroArchivo = 1;
    string extensionArchivo = ".txt";
    while (true) {
        ifstream creacion(nombreArchivo + to_string(numeroArchivo) + extensionArchivo);
        if (!creacion) break;
        creacion.close();
        numeroArchivo++;
    }
    string nombreCompletoArchivo = nombreArchivo + to_string(numeroArchivo) + extensionArchivo;
    ofstream creacion(nombreCompletoArchivo);
    creacion << "DATOS DEL VENDEDOR" << endl;
    creacion << "Nombre: " << vendedor.nombreVendedor << endl;
    creacion << "Direccion: " << vendedor.direccionVendedor << endl;
    creacion << "Telefono: " << vendedor.telefonoVendedor << endl;
    creacion << "ID: " << vendedor.idVendedor << endl << endl;
    
    creacion << "DATOS DEL CLIENTE" << endl;
    creacion << "Nombre: " << cliente.nombreCliente << endl;
    creacion << "Direccion: " << cliente.direccionCliente << endl;
    creacion << "Telefono: " << cliente.telefonoCliente << endl;
    creacion << "Fecha: " << cliente.fechaVenta << endl << endl;
    
    creacion << "Ventas registradas:" << endl << endl;
    for (int i = 0; i < ventas.size(); i++) {
        creacion << "Venta #" << i+1 << ":" << endl;
        for (int j = 0; j < ventas[i].productos.size(); j++) {
            ventas[i].productos[j].precioVenta = ventas[i].productos[j].precioVenta * ventas[i].productos[j].cantidad;
            creacion << "Producto: " << ventas[i].productos[j].nombre << " - Cantidad: " << ventas[i].productos[j].cantidad << " - Precio: " << ventas[i].productos[j].precioVenta << endl;
        }
        creacion << "Total: " << ventas[i].total << endl;
        creacion << "Metodo de Pago: " << ventas[i].metodoPago << endl << endl;
    }
    creacion.close();
    system("pause");
}

// MENU
int main(){
    do{
        system("cls");
        cout << "MENU DE OPCIONES"<<endl;
        cout << "1. Compras" << endl;
        cout << "2. Consultar Inventario" << endl;
        cout << "3. Busqueda de Producto" << endl;
        cout << "4. Eliminacion de Productos" << endl;
        cout << "5. Realizar Venta" << endl;
        cout << "6. Salir" << endl;
        cin >> seleccionMenu;

        switch (seleccionMenu){
        case 1: compraProductos();  break;
        case 2: consultarInventario(); system("pause"); break;
        case 3: busquedaProductos(); break;
        case 4: eliminacionProductos(); break;
        case 5: registrarVentas(); break;
        case 6: cout << "¡¡¡GRACIAS POR TU VISITA VUELVE PRONTO!!!" << endl; exit(0); break;
        default: cout << "Ingreso una opcion no valida" << endl; system("pause"); break;
        }
    } while (seleccionMenu != 8);
    return 0;
}