package com.sabanciuniv.model;


import java.util.List;
 
//just for communication
public class TransactionHelper 
{
	public String message;
	public List<transactionEmbeddedAccount> data;
	
	public TransactionHelper() {
		super();
	}

	public TransactionHelper(String message, List<transactionEmbeddedAccount> data) {
		super();
		this.message = message;
		this.data = data;
	}

	public String getMessage() {
		return message;
	}

	public void setMessage(String message) {
		this.message = message;
	}

	public List<transactionEmbeddedAccount> getData() {
		return data;
	}

	public void setData(List<transactionEmbeddedAccount> data) {
		this.data = data;
	}

	
	
	
	

}
