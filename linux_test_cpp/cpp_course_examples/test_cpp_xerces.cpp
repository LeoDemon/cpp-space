#include "test_cpp_xerces.h"
#include "test_cpp_main.h"


/**
 *  Constructor initializes xerces-C libraries.
 *  The XML tags and attributes which we seek are defined.
 *  The xerces-C DOM parser infrastructure is initialized.
 */

void GetFileData(const char *fileName, string &strInfo)
{
	ifstream infile(fileName);//默认为ios::in
	if(!infile)
	{
		cout<<"...infile "<<fileName<<" open error..."<<endl;
		exit(-1);
	}
	string strtmp("");
	while(getline(infile, strtmp))  //get函数，每次读入一个字符进行判断
	{
		strInfo += strtmp;
	}
	infile.close();
	cout<<strInfo<<endl;
}

GetConfig::GetConfig()
{
	try
	{
		XMLPlatformUtils::Initialize();  // Initialize Xerces infrastructure
	}
	catch( XMLException& e )
	{
		char* message = XMLString::transcode( e.getMessage() );
		cerr << "XML toolkit initialization error: " << message << endl;
		XMLString::release( &message );
		// throw exception here to return ERROR_XERCES_INIT
	}

	// Tags and attributes used in XML file.
	// Can't call transcode till after Xerces Initialize()
	// XMLString.transcode() 这个方法有多个重载，既可以把 XMLCh * 格式的数据转换成 char * 的数据，也可以把 char * 的数据转换成 XMLCh *
	TAG_root        = XMLString::transcode("root");
	TAG_ApplicationSettings = XMLString::transcode("ApplicationSettings");
	ATTR_OptionA = XMLString::transcode("option_a");
	ATTR_OptionB = XMLString::transcode("option_b");

	XMLTan = new XMLStringTan("utf-8");
	m_ConfigFileParser = new XercesDOMParser;
	m_ptRootEl = NULL;
}

/**
 *  Class destructor frees memory used to hold the XML tag and
 *  attribute definitions. It als terminates use of the xerces-C
 *  framework.
 */

GetConfig::~GetConfig()
{
	// Free memory
	delete XMLTan;
	delete m_ConfigFileParser;
	/*if(m_OptionA)   XMLString::release( &m_OptionA );*/
	/*if(m_OptionB)   XMLString::release( &m_OptionB );*/

	try
	{
		XMLString::release( &TAG_root );

		XMLString::release( &TAG_ApplicationSettings );
		XMLString::release( &ATTR_OptionA );
		XMLString::release( &ATTR_OptionB );
	}
	catch( ... )
	{
		cerr << "Unknown exception encountered in TagNamesdtor" << endl;
	}

	// Terminate Xerces
	try
	{
		XMLPlatformUtils::Terminate();  // Terminate after release of memory
	}
	catch( xercesc::XMLException& e )
	{
		char* message = xercesc::XMLString::transcode( e.getMessage() );
		cerr << "XML ttolkit teardown error: " << message << endl;
		XMLString::release( &message );
	}
}

/**
 *  This function:
 *  - Tests the access and availability of the XML configuration file.
 *  - Configures the xerces-c DOM parser.
 *  - Reads and extracts the pertinent information from the XML config file.
 *
 *  @param in configFile The text string name of the HLA configuration file.
 */

void GetConfig::readConfigFile(const char  *configFile) throw( std::runtime_error )
{
	// Test to see if the file is ok.

	struct stat fileStatus;

	errno = 0;
	if(stat(configFile, &fileStatus) == -1) // ==0 ok; ==-1 error
	{
		if( errno == ENOENT )      // errno declared by include file errno.h
			throw ( std::runtime_error("Path file_name does not exist, or path is an empty string.") );
		else if( errno == ENOTDIR )
			throw ( std::runtime_error("A component of the path is not a directory."));
		else if( errno == ELOOP )
			throw ( std::runtime_error("Too many symbolic links encountered while traversing the path."));
		else if( errno == EACCES )
			throw ( std::runtime_error("Permission denied."));
		else if( errno == ENAMETOOLONG )
			throw ( std::runtime_error("File can not be read\n"));
	}

	// Configure DOM parser.
	m_ConfigFileParser->setValidationScheme( XercesDOMParser::Val_Auto );
	m_ConfigFileParser->setDoNamespaces( false );
	m_ConfigFileParser->setDoSchema( false );
	m_ConfigFileParser->setLoadExternalDTD( false );

	try
	{
		//load parsing xml file
		m_ConfigFileParser->parse(configFile);

		// no need to free this pointer - owned by the parent parser object
		// get xml file's tree stucture
		DOMDocument* xmlDoc = m_ConfigFileParser->getDocument();

		// Get the top-level element: NAme is "root". No attributes for "root"
		DOMElement* elementRoot = xmlDoc->getDocumentElement();
		if(!elementRoot) throw(std::runtime_error("empty XML document"));

		// Parse XML file for tags of interest: "ApplicationSettings"
		// Look one level nested within "root". (child of root)
		DOMNodeList*      children = elementRoot->getChildNodes();
		const  XMLSize_t nodeCount = children->getLength();
		cout<<"-------nodeCount=="<<nodeCount<<endl;
		/* //使用 DOMNodeIterator 类遍历树型结构*/
		//DOMNodeIterator *domit = xmlDoc->createNodeIterator(elementRoot, DOMNodeFilter::SHOW_TEXT, NULL, true);
		//for(DOMNode * current = (DOMNode *)domit->nextNode(); current != 0; current = (DOMNode *)domit->nextNode())
		//{
		//string strName = XMLString::transcode(current->getNodeName());
		//string strValue = XMLString::transcode(current->getNodeValue());
		//cout<<"+++++++++nodeName=="<<strName<<", nodeValue=="<<strValue<<endl;
		//}
		////使用 DOMTreeWalker 类遍历树型结构
		//DOMTreeWalker *walker = xmlDoc->createTreeWalker(elementRoot, DOMNodeFilter::SHOW_TEXT, NULL, true);
		//for(DOMNode *curr = walker->nextNode(); curr != 0; curr = walker->nextNode())
		//{
		//char  *strName = XMLString::transcode(curr->getNodeName());
		//char *strValue = XMLString::transcode(curr->getNodeValue());
		//cout<<"**********nodeName=="<<strName<<", nodeValue=="<<strValue<<endl;
		//XMLString::release(&strName);
		//XMLString::release(&strValue);
		/*}*/
		//使用子节点直接遍历树型结构
		for( XMLSize_t ix = 0; ix < nodeCount; ++ix )
		{
			DOMNode* currentNode = children->item(ix);
			/*add by leo, 20130901 */
			if(currentNode->getNodeType() == DOMNode::ELEMENT_NODE)
			{
				for(DOMNode *nodeItm = currentNode->getFirstChild(); nodeItm != 0; nodeItm = nodeItm->getNextSibling())
				{
					char *nodeName = NULL;
					nodeName = XMLString::transcode(nodeItm->getNodeName());
					//string nodeValue = XMLString::transcode(nodeItm->getNodeValue());
					string nodeValue = XMLTan->translate(nodeItm->getNodeValue() );
					XMLTan->TranslatorUTF8ToChinese(nodeValue);
					//这里获取的nodeName都是#text
					cout<<"----------nodeName=="<<nodeName<<", nodeValue=="<<nodeValue<<endl;
				}
			}
			/*add by leo, 20130901 */
		}

		DOMNode *pCursor = elementRoot->getFirstChild();
		while(pCursor != NULL)
		{
			if(pCursor->getNodeType() == DOMNode::ELEMENT_NODE)
			{
				DOMElement* pDepartment = (DOMElement *)pCursor;
				char *strName = XMLString::transcode(pDepartment->getNodeName()) ;
				//这里可以获得正确的nodeName
				cout<<"###---###---strName=="<<strName<<endl;
				XMLString::release(&strName);
			}
			pCursor = pCursor->getNextSibling();
		}

		// For all nodes, children of "root" in the XML tree.
		for( XMLSize_t xx = 0; xx < nodeCount; ++xx )
		{
			DOMNode* currentNode = children->item(xx);
			if( currentNode->getNodeType() &&  // true is not NULL
					currentNode->getNodeType() == DOMNode::ELEMENT_NODE ) // is element
			{
				// Found node which is an Element. Re-cast node as element
				DOMElement* currentElement = dynamic_cast< xercesc::DOMElement* >( currentNode );
				if( XMLString::equals(currentElement->getTagName(), TAG_ApplicationSettings))
				{
					// Already tested node as type element and of name "ApplicationSettings".
					// Read attributes of element "ApplicationSettings".
					const XMLCh* xmlch_OptionA
						= currentElement->getAttribute(ATTR_OptionA);
					m_OptionA = XMLString::transcode(xmlch_OptionA);

					const XMLCh* xmlch_OptionB
						= currentElement->getAttribute(ATTR_OptionB);
					m_OptionB = XMLString::transcode(xmlch_OptionB);

					break;  // Data found. No need to look at other elements in tree.
				}
			}
		}
	}
	catch( xercesc::XMLException& e )
	{
		char* message = xercesc::XMLString::transcode( e.getMessage() );
		ostringstream errBuf;
		errBuf << "Error parsing file: " << message << flush;
		XMLString::release( &message );
	}
	catch(std::runtime_error &re)
	{
		cout<<"--------runtime error=="<<re.what()<<endl;
		delete XMLTan;
		delete m_ConfigFileParser;
		throw(re);
	}
}

void GetConfig::getNodeList(DOMElement *pDomeNode)
{
	int i=0, n_nodes=0;
	DOMNodeList *ptNodeList = NULL;
	DOMElement	*node = NULL;

	if (pDomeNode->hasChildNodes())
	{
		ptNodeList = pDomeNode->getChildNodes();
		n_nodes = ptNodeList->getLength();
		cout<<"-------n_nodes=="<<n_nodes<<endl;

		for (i = 0; i < n_nodes; i++)
		{
			node=(DOMElement*)ptNodeList->item(i);
			string nodename = S(node->getNodeName());

			if(nodename == "#text")
				continue;
			cout <<"第 "<<i<<" 节点：【"<<nodename<<"】==";

			if(node->hasChildNodes())
			{
				DOMNodeList *pNodeList = node->getChildNodes();
				int nList = pNodeList->getLength();
				//cout<<"-------nList=="<<nList<<endl;
				if(nList > 1)
				{
					cout <<"节点：【"<<nodename <<"】";
					cout <<"该节点为列表节点" <<endl;

					getNodeList(node);
					//utAddStruct(uTmp,nodename.c_str(),rp);
					cout <<"子节点：【"<<nodename <<"/】";
				}
				else
				{
					if(node->getFirstChild())
					{
						string nodevalue = S(node->getFirstChild()->getNodeValue());
						cout <<"【"<<nodevalue <<"】"<<endl;
						//utAddStr(uTmp,nodename.c_str(),nodevalue.c_str());
					}
					else
					{
						cout << "空节点" <<endl;
					}
				}
			}
			else
			{
				cout << "[null]" <<endl;
			}

		}
	}
}

void GetConfig::getXmlInfo()
{
	//获取根节点的名称
	string nodename = S(m_ptRootEl->getNodeName());
	cout<<"------------------in getXmlInfo........."<<endl;
	getNodeList(m_ptRootEl);
	cout<<"------------------out getXmlInfo........."<<endl;
	//utAddStruct(uXml,nodename.c_str(),rp);
	//LogUtype(uXml);
	//return uXml.release();
}

int GetConfig::DoParseXml(string &psData) throw( std::runtime_error )
{
	// Configure DOM parser.
	m_ConfigFileParser->setValidationScheme( XercesDOMParser::Val_Auto );
	m_ConfigFileParser->setDoNamespaces( false );
	m_ConfigFileParser->setDoSchema( false );
	m_ConfigFileParser->setLoadExternalDTD( false );

	DOMDocument* m_ptOutDoc = NULL;
	XMLCh* psXmlStr = NULL;
	int iErr = 0;
	string strtmp = psData;
	int len1 = strtmp.find("<?xml");
	int len2 = strtmp.find("?>");

	//目前只支持utf-16的格式
	if(len1 >=0 && len2 >0)
	{
		strtmp.replace(len1,len2+2,"<?xml version=\"1.0\" encoding=\"utf-16\" ?>");
	}
	cout<<"-------strtmp======="<<strtmp<<endl;
	psXmlStr = XMLString::transcode(strtmp.c_str());
	cout<<"------123"<<endl;

	try
	{
		MemBufInputSource* ptMemBufIS = new MemBufInputSource((const XMLByte*)psXmlStr, XMLString::stringLen(psXmlStr)*2, "Interface", false);
		cout<<"------456"<<endl;
		m_ConfigFileParser->parse(*ptMemBufIS);
		cout<<"------789"<<endl;
	}
	catch (const OutOfMemoryException&)
	{
		fprintf(stderr, "内存不足，解析XML失败！\n");
		goto END;
	}
	catch (const XMLException&)
	{
		goto END;
	}

	cout<<"------999"<<endl;
	m_ptOutDoc = m_ConfigFileParser->getDocument();
	if (!m_ptOutDoc)
	{
		goto END;
	}

	cout<<"------888"<<endl;
	m_ptRootEl=(DOMElement*)m_ptOutDoc->getDocumentElement();
	cout<<"------kkk"<<endl;
	if (!m_ptRootEl)
	{
		cout << "error:" <<endl;
		goto END;
	}
	cout<<"------fff"<<endl;
END:
	if (psXmlStr)
	{
		cout<<"------666"<<endl;
		XMLString::release(&psXmlStr);
	}

	return(iErr);
}

XMLStringTan::XMLStringTan(const char * const encoding):fFormatter(0), m_value(0),fEncodingUsed(0),toFill(0)
{
	XMLFormatTarget * myFormTarget = this;
	fEncodingUsed=XMLString::transcode(encoding);
	fFormatter = new XMLFormatter(fEncodingUsed, myFormTarget, XMLFormatter::NoEscapes, XMLFormatter::UnRep_CharRef);
	toFill=new XMLCh[kTmpBufSize];
	clearbuffer();
}

XMLStringTan::~XMLStringTan()
{
	if(fFormatter)
		delete fFormatter;
	if(fEncodingUsed)
		delete []  fEncodingUsed;
	if(m_value)
		free(m_value);
	if(toFill)
		free(toFill);

	fFormatter = 0;
	fEncodingUsed = 0;
	m_value = 0;
	toFill = 0;
}

void XMLStringTan::clearbuffer()
{
	if(!toFill)
		return;
	for(int i=0;i<kTmpBufSize;i++)
		toFill[i]=0;
}

//XMLCh* 转换到 string
string XMLStringTan::translate(const XMLCh* const value)
{
	*fFormatter<<value;
	string strValue=string(m_value);
	return strValue;
}

const XMLCh * const XMLStringTan::translate(const char * const value)
{
	clearbuffer();
	const unsigned int srcCount = XMLString::stringLen(value);
	unsigned char fCharSizeBuf[kCharBufSize];
	XMLTranscoder * pTranscoder=(XMLTranscoder *)fFormatter->getTranscoder();
	unsigned int bytesEaten;
	unsigned int size = pTranscoder->transcodeFrom((XMLByte*)value, srcCount, toFill, kTmpBufSize, (XMLSize_t &)bytesEaten, fCharSizeBuf);
	toFill[size]=0;
	string t1=string(value);
	string t2=translate(toFill);
	assert(t1==t2);
	return toFill;
}

bool XMLStringTan::UTF8_2_GB2312(char *in, int inLen, char *out, int outLen)
{
	iconv_t cd = iconv_open( "GB2312", "utf-8" );
	// check cd
	if(cd == 0)
	{
		cout << "iconv is ERROR" << endl;
		return false;
	}
	char *pin = in, *pout = out;
	int inLen_ = inLen + 1;
	int outLen_ = outLen;

	iconv(cd, &pin, (size_t*)&inLen_, &pout, (size_t*)&outLen_);
	iconv_close(cd);
	return true;
}

bool XMLStringTan::TranslatorUTF8ToChinese(string &strTranslatorMsg)
{
	char *pstrSource = const_cast<char*>(strTranslatorMsg.c_str());
	//char pstrDestination[strTranslatorMsg.length()*2 + 1]
	//如此处编译出错，可改为char
	char *pstrDestination = new char[strTranslatorMsg.length()*2+1];
	memset(pstrDestination, '\0', strTranslatorMsg.length()*2+1);
	if(!UTF8_2_GB2312(pstrSource, strTranslatorMsg.length(), pstrDestination, strTranslatorMsg.length()))
		return false;

	strTranslatorMsg = pstrDestination;
	free(pstrDestination);
	return true;
}


extern "C" int TestXerces(const char *puIn)
{
	cout<<"------puIn=="<<puIn<<endl;

	string strInfo("");
	GetFileData(puIn, strInfo);
	try
	{
		GetConfig appConfig;

		//appConfig.readConfigFile(puIn);
		appConfig.DoParseXml(strInfo);
		appConfig.getXmlInfo();

		cout<<"------ppp"<<endl;
		/*cout << "Application option A="  << appConfig.getOptionA()  << endl;*/
		/*cout << "Application option B="  << appConfig.getOptionB()  << endl;*/
	}
	catch(std::runtime_error &re)
	{
		exit(-2);
	}

	return 0;
}

