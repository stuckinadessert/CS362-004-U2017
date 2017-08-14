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
   private boolean removeTrueValues = true;	//If true, removes the print calls from the console feed. 
   public UrlValidatorTest(String testName) {
      super(testName);
   }
   
   //Comparison function.
   //provides more information if a test status fails. Enables procedural processing.
   //In short, this exists so that the 
   private void mPrintValidation(UrlValidator mValid, ResultPair mPair) {
	   boolean result = mValid.isValid(mPair.item);
	   if (!result && mPair.valid == false) {
		   if (!removeTrueValues) {System.out.println(true);}
	   }
	   else if (result && mPair.valid == true) {
		   if (!removeTrueValues) {System.out.println(true);}
	   }else{
		   System.out.println("URL: \"" + mPair.item + "\" Failed. isValid returned:" + result + ". Expected:" + mPair.valid);
		   //assertTrue("test of assertion",false);
	   }  
   }
   
   private void mStringMaker(Object[] testpartsinput, Integer[] index) {
	   
	   
   }
   /* ***********************
    * Manual Test
    * URL Validator flags:
    * ALLOW_ALL_SCHEMES
    * ALLOW_2_SLASHES
    * NO_FRAGMENTS
    * ALLOW_LOCAL_URLS 
    * ***********************/
   public void testManualTest()
   {
	   UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
	   //Array of manual tests and expected outcomes
	   ResultPair[] aTestUrls = {new ResultPair("http://www.amazon.com",true),
			   					new ResultPair("http://www.google.com",true),
			   					new ResultPair("http://www.google.com/",true),
			   					new ResultPair("https://youtube.com",true),
			   					new ResultPair("https://www.youtube.com/channel/UCqW2IE1q5nLArY1LPYZmEuw",true),
			   					new ResultPair("http://www.aspiswinnebago.com",true),
			   					new ResultPair("htp://www.google.com",true),
			   					new ResultPair("ftp://www.google.com",true),
			   					new ResultPair("mailto://www.google.com",true),
			   					new ResultPair("irc://www.google.com",true),
			   					new ResultPair("http//www.google.com",false),
			   					new ResultPair("http://localhost:8000/", false),
			   					new ResultPair("http://localhost:3000",false),
			   					new ResultPair(null,false),
			   					new ResultPair("http://-1", false),
			   					new ResultPair("ftp://www.am.co.net", true),
			   					new ResultPair("randomtext",false),
			   					new ResultPair("1.255.255.255", false),
			   					new ResultPair("file://",true)
			   					};
	   							
	   for (int i=0;i<aTestUrls.length;i++) {
		   mPrintValidation(urlVal,aTestUrls[i]);
	   }
	   
	   urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES + UrlValidator.ALLOW_LOCAL_URLS);
	   
	   ResultPair[] bTestUrls = {new ResultPair("http://www.amazon.com",true),
								new ResultPair("http://www.google.com",true),
								new ResultPair("http://www.google.com/",true),
								new ResultPair("https://youtube.com",true),
								new ResultPair("https://www.youtube.com/channel/UCqW2IE1q5nLArY1LPYZmEuw",true),
								new ResultPair("http://www.aspiswinnebago.com",true),
								new ResultPair("htp://www.google.com",true),
								new ResultPair("ftp://www.google.com",true),
								new ResultPair("mailto://www.google.com",true),
								new ResultPair("irc://www.google.com",true),
								new ResultPair("http//www.google.com",false),
								new ResultPair("http://localhost:8000/", true), //Should be enabled by ALLOW_LOCAL_URLS
								new ResultPair("http://localhost:3000",true),	//Should be enabled by ALLOW_LOCAL_URLS
								new ResultPair(null,false),
								new ResultPair("http://-1", false),				//Bug within Local URLS allows invalid address
								new ResultPair("ftp://www.am.co.net", true),
								new ResultPair("randomtext",false),
								new ResultPair("1.255.255.255", false),
								new ResultPair("file://",true)
								};	  
	   for (int i=0;i<bTestUrls.length;i++) {
		   mPrintValidation(urlVal,bTestUrls[i]);
	   }	   
		
urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_LOCAL_URLS);
	   
	   ResultPair[] cTestUrls = {new ResultPair("http://www.amazon.com",true),
								new ResultPair("http://www.google.com",true),
								new ResultPair("http://www.google.com/",true),
								new ResultPair("https://youtube.com",true),
								new ResultPair("https://www.youtube.com/channel/UCqW2IE1q5nLArY1LPYZmEuw",true),
								new ResultPair("http://www.aspiswinnebago.com",true),
								new ResultPair("htp://fr.google.com",true),
								new ResultPair("ftp://www.google.gov/en_ru/",true),
								new ResultPair("mailto://www.google.com",false),
								new ResultPair("irc://www.google.com",false),
								new ResultPair("http//us.google.com",false),
								new ResultPair("http://localhost:8000/", true), //Should be enabled by ALLOW_LOCAL_URLS
								new ResultPair("http://localhost:3000",true),	//Should be enabled by ALLOW_LOCAL_URLS
								new ResultPair(null,false),
								new ResultPair("http://-1", false),				//Bug within ALLOW_LOCAL_URLS enables invalid address
								new ResultPair("ftp://www.am.co.net", true),
								new ResultPair("randomtext",false),
								new ResultPair("1.255.255.255", false),
								new ResultPair("file://",true)					//Local file Should be valid.
								};	  
	   for (int i=0;i<cTestUrls.length;i++) {
		   mPrintValidation(urlVal,cTestUrls[i]);
	   }

	   //Test Default validator. Default domains exclude all values other than http/ftp/ and https
	   urlVal = new UrlValidator();
	   ResultPair[] dTestUrls = {new ResultPair("http://www.amazon.com",true),
				new ResultPair("http://www.google.com",true),				
				new ResultPair("https://www.youtube.com/channel/UCqW2IE1q5nLArY1LPYZmEuw",true),
				new ResultPair("ftp://www.google.gov/en_ru/",true),
				new ResultPair("mailto://www.google.com",false),
				new ResultPair("irc://www.google.com",false),
				new ResultPair("http//us.google.com",false),
				new ResultPair("http://localhost:8000/", false),
				new ResultPair("http://localhost:3000",false),
				new ResultPair(null,false),
				new ResultPair("http://-1", false),				
				new ResultPair("ftp://www.am.co.net", true),
				new ResultPair("randomtext",false),
				new ResultPair("http://180.0.0.1:80", true),
				new ResultPair("http://2001:4860:4860::8888",true),	//2001:4860:4860::8888 is Google's IPv6 address
				new ResultPair("http://180.-2.0.20:10", false),
				new ResultPair("file://",false),
				new ResultPair("http://www.google.com//notallowed.",false)
				};	  
	   for (int i=0;i<dTestUrls.length;i++) {
		   mPrintValidation(urlVal,dTestUrls[i]);
	   }
	   
	   urlVal = new UrlValidator(null,null, UrlValidator.ALLOW_2_SLASHES);
	   ResultPair[] eTestUrls = {new ResultPair("http://www.amazon.com",true),
				new ResultPair("http://www.google.com//nowallowed.",true)
				};	  
	   for (int i=0;i<eTestUrls.length;i++) {
		   mPrintValidation(urlVal,eTestUrls[i]);
	   }
   }
   
   
	/* ********************************************
	 * 
	 * 
	 * 
	 * ********************************************/
   
   
   public void testYourFirstPartition()
   {
	   
   }
   
   public void testYourSecondPartition(){
	   
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
   
   //These data sets have been pulled from the UrlValidatorTest.java file provided
   //from the URLValidatorCorrect project source code.
   //The purpose of this is to use them as data input points,
   //since they are more accurate than anything I could devise.
   //This will stay here until I have an answer from the professor as to whether or not
   //We can use them.
   ResultPair[] testUrlScheme = {new ResultPair("http://", true),
           new ResultPair("ftp://", true),
           new ResultPair("h3t://", true),
           new ResultPair("3ht://", false),
           new ResultPair("http:/", false),
           new ResultPair("http:", false),
           new ResultPair("http/", false),
           new ResultPair("://", false),
           new ResultPair("", true)};
   
   ResultPair[] testUrlAuthority = {new ResultPair("www.google.com", true),
	              new ResultPair("go.com", true),
	              new ResultPair("go.au", true),
	              new ResultPair("0.0.0.0", true),
	              new ResultPair("255.255.255.255", true),
	              new ResultPair("256.256.256.256", false),
	              new ResultPair("255.com", true),
	              new ResultPair("1.2.3.4.5", false),
	              new ResultPair("1.2.3.4.", false),
	              new ResultPair("1.2.3", false),
	              new ResultPair(".1.2.3.4", false),
	              new ResultPair("go.a", false),
	              new ResultPair("go.a1a", false),
	              new ResultPair("go.cc", true),
	              new ResultPair("go.1aa", false),
	              new ResultPair("aaa.", false),
	              new ResultPair(".aaa", false),
	              new ResultPair("aaa", false),
	              new ResultPair("", false)};
	ResultPair[] testUrlPort = {new ResultPair(":80", true),
	         new ResultPair(":65535", true),
	         new ResultPair(":0", true),
	         new ResultPair("", true),
	         new ResultPair(":-1", false),
	         new ResultPair(":65636", true),
	         new ResultPair(":65a", false)};
	ResultPair[] testPath = {new ResultPair("/test1", true),
	      new ResultPair("/t123", true),
	      new ResultPair("/$23", true),
	      new ResultPair("/..", false),
	      new ResultPair("/../", false),
	      new ResultPair("/test1/", true),
	      new ResultPair("", true),
	      new ResultPair("/test1/file", true),
	      new ResultPair("/..//file", false),
	      new ResultPair("/test1//file", false)
	};
	//Test allow2slash, noFragment
	ResultPair[] testUrlPathOptions = {new ResultPair("/test1", true),
	                new ResultPair("/t123", true),
	                new ResultPair("/$23", true),
	                new ResultPair("/..", false),
	                new ResultPair("/../", false),
	                new ResultPair("/test1/", true),
	                new ResultPair("/#", false),
	                new ResultPair("", true),
	                new ResultPair("/test1/file", true),
	                new ResultPair("/t123/file", true),
	                new ResultPair("/$23/file", true),
	                new ResultPair("/../file", false),
	                new ResultPair("/..//file", false),
	                new ResultPair("/test1//file", true),
	                new ResultPair("/#/file", false)
	};
	
	ResultPair[] testUrlQuery = {new ResultPair("?action=view", true),
	          new ResultPair("?action=edit&mode=up", true),
	          new ResultPair("", true)
	};
	
	Object[] testUrlParts = {testUrlScheme, testUrlAuthority, testUrlPort, testPath, testUrlQuery};
	Object[] testUrlPartsOptions = {testUrlScheme, testUrlAuthority, testUrlPort, testUrlPathOptions, testUrlQuery};
	int[] testPartsIndex = {0, 0, 0, 0, 0};

  }
