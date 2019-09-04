import wikipediaapi

if __name__ == "__main__":
    import sys
    lang = sys.argv[1]
    search = sys.argv[2]

wiki = wikipediaapi.Wikipedia(lang)
page_py = wiki.page(search)
print(page_py.text)
