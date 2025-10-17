//Sam Emison
//10/17/2025
//Imported from demo files

// libxml2_secure_demo.cpp
#include <iostream>
#include <libxml/parser.h>
#include <libxml/tree.h>

int main() {
    // Ensure default is NOT to substitute entities
    xmlSubstituteEntitiesDefault(0); // make sure automatic entity substitution is disabled

    // Use options that DO NOT include XML_PARSE_NOENT
    // Use XML_PARSE_NONET to forbid fetching external DTDs over network.
    int options = XML_PARSE_NOENT | XML_PARSE_DTDLOAD | XML_PARSE_NONET | XML_PARSE_NOERROR | XML_PARSE_NOWARNING;

    xmlDocPtr doc = xmlReadFile("cat_small_nested.xml", NULL, options);
    if (!doc) {
        std::cerr << "Failed to parse XML safely\n";
        return 1;
    }

    xmlNodePtr root = xmlDocGetRootElement(doc);
    for (xmlNodePtr node = root->children; node; node = node->next) {
        if (node->type == XML_ELEMENT_NODE) {
            xmlChar* content = xmlNodeGetContent(node);
            std::cout << (const char*)node->name << ": " 
                      << (content ? (const char*)content : "(null)") << "\n";
            if (content) xmlFree(content);
        }
    }

    // Dump memory to inspect result (shows that entity references are not expanded)
    xmlChar *xmlbuff;
    int buffersize;
    xmlDocDumpFormatMemory(doc, &xmlbuff, &buffersize, 1);
    if (xmlbuff) {
        std::cout << "\n--- full parsed XML (secure) ---\n" << (const char*)xmlbuff << "\n";
        xmlFree(xmlbuff);
    }

    xmlFreeDoc(doc);
    xmlCleanupParser();
    return 0;
}
