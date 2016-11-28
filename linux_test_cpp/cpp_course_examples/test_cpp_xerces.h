#ifndef XML_PARSER_HPP
#define XML_PARSER_HPP
/**
 *  @file
 *  Class "GetConfig" provides the functions to read the XML data.
 *  @version 1.0
 */
#include <xercesc/dom/DOM.hpp>
#include <xercesc/dom/DOMDocument.hpp>
#include <xercesc/dom/DOMDocumentType.hpp>
#include <xercesc/dom/DOMElement.hpp>
#include <xercesc/dom/DOMImplementation.hpp>
#include <xercesc/dom/DOMImplementationLS.hpp>
#include <xercesc/dom/DOMNodeIterator.hpp>
#include <xercesc/dom/DOMNodeList.hpp>
#include <xercesc/dom/DOMText.hpp>
#include <xercesc/dom/DOMAttr.hpp>

#include <xercesc/parsers/XercesDOMParser.hpp>

#include <xercesc/util/XMLString.hpp> 
#include <xercesc/util/XMLUni.hpp>
#include <xercesc/util/TransService.hpp>

#include <xercesc/framework/XMLFormatter.hpp>
#include <xercesc/framework/MemBufInputSource.hpp>
#include <xercesc/util/OutOfMemoryException.hpp>

#include <stdlib.h>
#include <string>
#include <list>
#include <stdexcept>
#include <iconv.h>

using namespace xercesc;
// Error codes
enum {
	ERROR_ARGS = 1,
	ERROR_XERCES_INIT,
	ERROR_PARSE,
	ERROR_EMPTY_DOCUMENT
};

class XStr
{
public :
    // -----------------------------------------------------------------------
    //  Constructors and Destructor
    // -----------------------------------------------------------------------
    XStr(const char* const toTranscode)
    {
        // Call the private transcoding method
        fUnicodeForm = XMLString::transcode(toTranscode);
    }

    ~XStr()
    {
        XMLString::release(&fUnicodeForm);
    }


    // -----------------------------------------------------------------------
    //  Getter methods
    // -----------------------------------------------------------------------
    const XMLCh* unicodeForm() const
    {
        return fUnicodeForm;
    }

private :
    // -----------------------------------------------------------------------
    //  Private data members
    //
    //  fUnicodeForm
    //      This is the Unicode XMLCh format of the string.
    // -----------------------------------------------------------------------
    XMLCh*   fUnicodeForm;
};

#define X(str) XStr(str).unicodeForm()


const char* const g_nullStr="";
// ---------------------------------------------------------------------------
//  This is a simple class that lets us do easy (though not terribly efficient)
//  trancoding of XMLCh data to local code page for display.
// ---------------------------------------------------------------------------
class StrX
{
public :
    // -----------------------------------------------------------------------
    //  Constructors and Destructor
    // -----------------------------------------------------------------------
    StrX(const XMLCh* const toTranscode)
    {
		if (!toTranscode)
		{
			//指向一个空串。保证返回的串不为空。
			fLocalForm = (char*)g_nullStr;
		}
		else
		{
			// Call the private transcoding method
			fLocalForm = XMLString::transcode(toTranscode);
		}
    }

    ~StrX()
    {
		if (fLocalForm != g_nullStr)
		{
			XMLString::release(&fLocalForm);
		}
    }


    // -----------------------------------------------------------------------
    //  Getter methods
    // -----------------------------------------------------------------------
    const char* localForm() const
    {
        return fLocalForm;
    }

private :
    // -----------------------------------------------------------------------
    //  Private data members
    //
    //  fLocalForm
    //      This is the local code page form of the string.
    // -----------------------------------------------------------------------
    char*   fLocalForm;
};

#define S(str) StrX(str).localForm()
/*---------------------------------XML END-------------------------------------------------------*/


class XMLStringTan;
class GetConfig
{
	public:
		GetConfig();
		~GetConfig();
		void readConfigFile(const char *) throw(std::runtime_error);
		int DoParseXml(std::string &) throw(std::runtime_error);
		void getNodeList(xercesc::DOMElement *pDomeNode);
		void getXmlInfo();
		void getConfigFile(std::string &) throw(std::runtime_error);

		char *getOptionA() { return m_OptionA; };
		char *getOptionB() { return m_OptionB; };

	public:
		XMLStringTan *XMLTan;
		xercesc::XercesDOMParser *m_ConfigFileParser;
		char* m_OptionA;
		char* m_OptionB;

		// Internal class use only. Hold Xerces data in UTF-16 SMLCh type.

		XMLCh* TAG_root;

		XMLCh* TAG_ApplicationSettings;
		XMLCh* ATTR_OptionA;
		XMLCh* ATTR_OptionB;
		xercesc::DOMElement* m_ptRootEl;
};

//记得使用命名空间
class XMLStringTan:public xercesc::XMLFormatTarget
{
	public:
		XMLStringTan(const char * const encoding);
		bool TranslatorUTF8ToChinese(std::string &strTranslatorMsg);
		bool UTF8_2_GB2312(char *in, int inLen, char *out, int outLen);
		std::string translate(const XMLCh* const value);
		const XMLCh * const translate(const char * const value);
		~XMLStringTan();

	private:
		xercesc::XMLFormatter *fFormatter;
		XMLCh *fEncodingUsed;
		XMLCh *toFill;
		char *m_value;

	public:
		enum Constants
		{
			kTmpBufSize = 16*1024,
			kCharBufSize = 16*1024
		};
		void clearbuffer();
		void writeChars(const XMLByte* const toWrite, const XMLSize_t count, xercesc::XMLFormatter* const formatter);
};

void XMLStringTan::writeChars(const XMLByte* const toWrite, const XMLSize_t count, xercesc::XMLFormatter* const formatter)
{
	//XMLFormatTarget::writeChars(toWrite, count, formatter);
	m_value = (char *)malloc(count + 1);
	memset(m_value,0,count+1);
	memcpy(m_value, (char *)toWrite, count);
}

#endif

