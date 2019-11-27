#pragma once
#include <iostream>

template<typename _type> 
class Node
{
public:
	Node<_type>();
	Node<_type>(_type dato);
	Node<_type>(_type dato, Node<_type> * sig);
	void CargaDato(_type dato);
	void Set_siguiente(Node<_type>* nuevo);
	
	_type Get_dato();
	Node<_type> * Get_siguiente();

	void MostrarNodo();
	
private:
	_type Dato;
	Node<_type>* sig;
};

template<typename _type>
inline Node<_type>::Node()
	: sig(nullptr)
{

}

template<typename _type>
inline Node<_type>::Node(_type dato)
	: Dato(dato) ,sig(nullptr)
{
	/*this->Dato = dato;
	this->sig = nullptr;*/
}

template<typename _type>
inline Node<_type>::Node(_type dato, Node<_type>* Nuevo)
	:Dato(dato), sig(Nuevo)
{
	/*
	this->Dato = dato;
	this->sig = Nuevo;*/
}

template<typename _type>
inline void Node<_type>::CargaDato(_type dato)
{
	this->Dato = dato;
}

template<typename _type>
inline _type Node<_type>::Get_dato()
{
	return _type(Dato);
}

template<typename _type>
inline Node<_type>* Node<_type>::Get_siguiente()
{
	return sig;
}



template<typename _type>
inline void Node<_type>::MostrarNodo()
{
	std::cout << "---------------------" << "\n" <<
		"Dato en Nodo : " << Dato << "\n" <<
		"---------------------" << std::endl;

}

template<typename _type>
inline void Node<_type>::Set_siguiente(Node<_type>* nuevo)
{
	this->sig = nuevo;
}
