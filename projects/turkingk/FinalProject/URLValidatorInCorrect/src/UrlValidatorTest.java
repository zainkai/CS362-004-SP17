/*
 * Licensed to the Apache Software Foundation (ASF) under one or more
 * contributor license agreements.  See the NOTICE file distributed with
 * this work for additional information regarding copyright ownership.
 * The ASF licenses this file to You under the Apache License, Version 2.0
 * (the "License"); you may not use this file except in compliance with
 * the License.  You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */


import junit.framework.TestCase;





/**
 * Performs Validation Test for url validations.
 *
 * @version $Revision: 1128446 $ $Date: 2011-05-27 13:29:27 -0700 (Fri, 27 May 2011) $
 */
public class UrlValidatorTest extends TestCase {
    
    
    private boolean printStatus = false;
    private boolean printIndex = false;//print index that indicates current scheme,host,port,path, query test were using.
    
    public UrlValidatorTest(String testName) {
        super(testName);
    }
    
    public void testManualTest()
    {
        
        UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
        
        System.out.println(urlVal.isValid("http://www.amazon.com"));
        System.out.println(urlVal.isValid("https://www.google.com"));
        System.out.println(urlVal.isValid("https://www.google.com/%20Test"));
        System.out.println(urlVal.isValid("https://www.google.com/%20Test:9000000"));
        System.out.println(urlVal.isValid("ftp://www.google.com/%20Test"));
        
        System.out.println(urlVal.isValid("https://///www.google.com"));
        System.out.println(urlVal.isValid("https://www.google.com /test"));// false postive
        System.out.println(urlVal.isValid("https://www.google.com:"));
        System.out.println(urlVal.isValid("https://www.google"));
        System.out.println(urlVal.isValid("ftpm://www.google.com/")); // false postive
        System.out.println(urlVal.isValid("Http://google.com"));
        System.out.println(urlVal.isValid("http://www.google.ca"));
        System.out.println(urlVal.isValid("http://localhost:8000")); // false negative
        System.out.println(urlVal.isValid("http://198.123.1:8000")); // false negative
    }
    
    public void testAllPartitions()
    {
        String test = "";
        boolean result;
        UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
        
        //Testing protocol + destination + port + requestString
        for(int i = 0; i < protocols.length; i++) {
            for(int j = 0; j < destination.length; j++) {
                for(int k = 0; k < portnumbers.length; k++) {
                    for(int l = 0; l < requestString.length; l++) {
                        test = test.concat(protocols[i].item)
                        .concat("://")
                        .concat(destination[j].item)
                        .concat(portnumbers[k].item)
                        .concat(requestString[l].item);
                        
                        result = urlVal.isValid(test);
                        
                        if((protocols[i].valid && destination[j].valid && portnumbers[k].valid && requestString[l].valid) && result){
                            System.out.println(test +" is valid");
                        }
                        else if((!protocols[i].valid && !destination[j].valid && !portnumbers[k].valid && !requestString[l].valid) && !result){
                            System.out.println(test +" is not valid");
                        }
                        else if((!protocols[i].valid || !destination[j].valid || !portnumbers[k].valid || !requestString[l].valid) && result){
                            //System.out.println(test);
                            //System.out.println("\treturned false positive");
                        }
                        else if((protocols[i].valid && destination[j].valid && portnumbers[k].valid && requestString[l].valid) && !result){
                            //System.out.println(test);
                            //System.out.println("\treturned false negative");
                        }
                        test = "";
                    }
                }
            }
        }
        
        //Testing protocol + destination + requestString (portnumber is optional in a valid URL)
        test = "";
        for(int i = 0; i < protocols.length; i++) {
            for(int j = 0; j < destination.length; j++) {
                for(int k = 0; k < requestString.length; k++) {
                    test = test.concat(protocols[i].item)
                    .concat("://")
                    .concat(destination[j].item)
                    .concat(requestString[k].item);
                    
                    result = urlVal.isValid(test);
                    
                    if((protocols[i].valid && destination[j].valid && requestString[k].valid) && result){
                        System.out.println(test +" is valid");
                    }
                    else if((!protocols[i].valid && !destination[j].valid && !requestString[k].valid) && !result){
                        System.out.println(test +" is not valid");
                    }
                    else if((!protocols[i].valid || !destination[j].valid || !requestString[k].valid) && result){
                        //System.out.println(test);
                        //System.out.println("\treturned false positive");
                    }
                    else if((protocols[i].valid && destination[j].valid && requestString[k].valid) && !result){
                        //System.out.println(test);
                        //System.out.println("\treturned false negative");
                    }
                    test = "";
                }
            }
        }
    }
    
    public void testYourFirstPartition()
    {
        String test = "";
        boolean result;
        UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
        
        //protocol and authority testing.
        for(int i = 0;i < protocols.length;i++){
            for(int j = 0;j<destination.length;j++){
                
                test = test.concat(protocols[i].item).concat("://").concat(destination[j].item);
                
                result = urlVal.isValid(test);
                
                if((protocols[i].valid && destination[j].valid) && result){
                    System.out.println(test +" is valid");
                }
                else if((!protocols[i].valid && !destination[j].valid) && !result){
                    System.out.println(test +" is not valid");
                }
                else if((!protocols[i].valid || !destination[j].valid) && result){
                    //System.out.println(test);
                    //System.out.println("\treturned false positive");
                }
                else if((protocols[i].valid && destination[j].valid) && !result){
                    //System.out.println(test);
                    //System.out.println("\treturned false negative");
                }
                test = "";
            }
        }
    }
    
    public void testYourSecondPartition(){
        String test = "http://www.google.com";
        boolean result;
        UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
        
        //only port
        for(int i = 0;i < portnumbers.length;i++){
            test = test.concat(portnumbers[i].item);
            
            result = urlVal.isValid(test);
            
            if(portnumbers[i].valid  && result){
                System.out.println(test +" is valid");
            }
            else if(!portnumbers[i].valid && !result){
                System.out.println(test +" is not valid");
            }
            else if(!portnumbers[i].valid && result){
                //System.out.println(test);
                //System.out.println("\treturned false positive");
            }
            else if(portnumbers[i].valid && !result){
                //System.out.println(test);
                //System.out.println("\treturned false negative");
            }
            test = "http://www.google.com";
        }
        
        //only resultstring
        test = "http://www.google.com";
        for(int i = 0;i < requestString.length;i++){
            test = test.concat(requestString[i].item);
            
            result = urlVal.isValid(test);
            
            if(requestString[i].valid  && result){
                System.out.println(test +" is valid");
            }
            else if(!requestString[i].valid && !result){
                System.out.println(test +" is not valid");
            }
            else if(!requestString[i].valid && result){
                //System.out.println(test);
                //System.out.println("\treturned false positive");
            }
            else if(requestString[i].valid && !result){
                //System.out.println(test);
                //System.out.println("\treturned false negative");
            }
            test = "http://www.google.com";
        }
        //port and resultstring testing.
        
        test = "";
        for(int i = 0;i < portnumbers.length;i++){
            for(int j = 0;j<requestString.length;j++){
                
                test = test.concat(portnumbers[i].item).concat(requestString[j].item);
                
                result = urlVal.isValid(test);
                
                if((portnumbers[i].valid && requestString[j].valid) && result){
                    System.out.println(test +" is valid");
                }
                else if((!portnumbers[i].valid && !requestString[j].valid) && !result){
                    System.out.println(test +" is not valid");
                }
                else if((!portnumbers[i].valid || !requestString[j].valid) && result){
                    //System.out.println(test);
                    //System.out.println("\treturned false positive");
                }
                else if((portnumbers[i].valid && requestString[j].valid) && !result){
                    //System.out.println(test);
                    //System.out.println("\treturned false negative");
                }
                test = "http://www.google.com";
            }
        }
    }
    
    
    public void testIsValid()
    {
        for(int i = 0;i<10000;i++)
        {
            
        }
    }
    
    public void testAnyOtherUnitTest()
    {
        
    }
    /**
     * Create set of tests by taking the testUrlXXX arrays and
     * running through all possible permutations of their combinations.
     *
     * @param testObjects Used to create a url.
     */
    ResultPair[] protocols = {
    new ResultPair("http",true),
    new ResultPair("ftp",true),
    new ResultPair("telnet",true),
    new ResultPair("https",true),
    new ResultPair("pbbt",false),
    new ResultPair("1337",false),
    new ResultPair("uwotM8",false),
    new ResultPair("HTTP",true),
    new ResultPair("Https",true),
    };
    
    ResultPair[] destination = {
    new ResultPair("www.google.com",true),
    new ResultPair("www.google.ca",true),
    new ResultPair("www.chaity.org",true),
    new ResultPair("www.BushDid911.conspiracy",false),
    new ResultPair("pbbt.com",true),
    new ResultPair("255.255.255.255",true),
    new ResultPair("32323.hello.com",false),
    new ResultPair("www__com.com",false),
    new ResultPair("ipv4.internet",false),
    };
    
    ResultPair[] requestString = {
    new ResultPair("helloWorld%21",true),
    new ResultPair("?helloWorld%21&321",true),
    new ResultPair("/tt/t/t/?helloWorld%21&321",true),
    new ResultPair("/tt/t/t/",true),
    new ResultPair("/#test",false),
    new ResultPair("/tt//t/t/",false),
    new ResultPair("/...t/t/",false),
    new ResultPair("/ test",false),
    new ResultPair("/%20test",true),
    };
    
    ResultPair[] portnumbers = {
    new ResultPair(":heyo",false),
    new ResultPair(":8000",true),
    new ResultPair(":10101",true),
    new ResultPair(":101",true),
    new ResultPair(":10",true),
    new ResultPair(":1",true),
    new ResultPair(":18888888888888888888",false),
    new ResultPair(":188pepe",false),
    
    };
    
}
