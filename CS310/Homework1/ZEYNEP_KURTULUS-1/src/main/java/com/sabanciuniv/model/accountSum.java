package com.sabanciuniv.model;

public class accountSum {
	
	String message;
	summaryHolder data;
	
	
	
	public accountSum() {
		super();
	}

	public String getMessage() {
		return message;
	}
	

	public void setMessage(String message) {
		this.message = message;
	}
	
	public summaryHolder getData() {
		return data;
	}


	public void setData(summaryHolder data) {
		this.data = data;
	}


	public accountSum(String message, summaryHolder data) {
		super();
		this.message = message;
		this.data = data;
		
		
	}


	


	



	

	
	
}
