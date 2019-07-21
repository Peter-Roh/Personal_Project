import wikipediaapi

if __name__ == "__main__":
    import sys
    search = sys.argv[1]

wiki = wikipediaapi.Wikipedia('ko')
page_py = wiki.page(search)
print(page_py.text)
