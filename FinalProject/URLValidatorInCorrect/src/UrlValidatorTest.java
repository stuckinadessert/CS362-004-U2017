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
   private boolean removeTrueValues = false;	//If true, removes the print calls from the console feed. 
   public UrlValidatorTest(String testName) {
      super(testName);
   }
   
   //Comparison function.
   //provides more information if a test status fails. Enables procedural processing.
   private void mPrintValidation(UrlValidator mValid, ResultPair mPair) {
	   boolean result = mValid.isValid(mPair.item);
	   if (!result && mPair.valid == false) {
		   if (removeTrueValues) {System.out.println(true);}
	   }
	   else if (result && mPair.valid == true) {
		   if (removeTrueValues) {System.out.println(true);}
	   }else{
		   System.out.println("URL: \"" + mPair.item + "\" Failed. isValid returned:" + result + ". Expected:" + mPair.valid);
	   }  
   }
   
   public void testManualTest()
   {
	   UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
	   //Array of manual tests and expected outcomes
	   ResultPair[] mTestUrls = {new ResultPair("http://www.amazon.com",true),
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
			   					new ResultPair("randomtext",false)};
	   for (int i=0;i<mTestUrls.length;i++) {
		   mPrintValidation(urlVal,mTestUrls[i]);
	   }
   }
   
   
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
   ResultPair[] testUrlScheme = {new ResultPair("htp", true),
		   						new ResultPair("http",true),
		   						new ResultPair("ftp",true),
		   						new ResultPair("https",true),
		   						new ResultPair("htps",false)};

}
