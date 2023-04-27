package com.sabanciuniv.repo;

import java.util.List;

import org.springframework.data.mongodb.repository.MongoRepository;
import com.sabanciuniv.model.Transaction;
import com.sabanciuniv.model.Account;

public interface AccountRepository extends MongoRepository<Account, String>{
	
	public List<Account> findByid(String Id);
}
