import requests
from bs4 import BeautifulSoup
import csv

# indeed

def extract_pages(url):
    result = requests.get(url)
    soup = BeautifulSoup(result.text, 'html.parser')
    pagination = soup.find("div", {"class": "pagination"})
    links = pagination.find_all("a")
    pages = []
    for page in links[:-1]:
        pages.append(int(page.string))
    max_page = pages[-1]
    return max_page

def extract_job(html):
    title = html.find("h2", {"class": "title"}).find("a")["title"]
    company = html.find("span", {"class": "company"})
    if company.find("a") is not None:
        company = str(company.find("a").string)
    else:
        company = str(company.string)
    company = company.strip()
    location = html.find("div", {"class": "recJobLoc"})["data-rc-loc"]
    job_id = html["data-jk"]
    return {
    "title": title, 
    "company": company, 
    "location": location, 
    "link": f"https://kr.indeed.com/jobs?q=python&limit=50&start=200&vjk={job_id}"
    }

def extract_jobs(last_page, url):
    jobs = []
    for page in range(last_page):
        print(f"Scrapping Indeed page {page + 1}...")
        result = requests.get(url+"&start={}".format(page*50))
        soup = BeautifulSoup(result.text, 'html.parser')
        results = soup.find_all("div", {"class": "jobsearch-SerpJobCard"})
        for item in results:
            job = extract_job(item)
            jobs.append(job)
    return jobs

# stackoverflow

def get_last_page(url_2):
    result = requests.get(url_2)
    soup = BeautifulSoup(result.text, "html.parser")
    pages = soup.find("div", {"class": "s-pagination"}).find_all("a")
    last_page = pages[-2].get_text(strip=True)
    return int(last_page)

def extract_so_job(html):
    title = html.find("h2").find("a")["title"]
    company_row = html.find("h3").find_all("span")
    company = company_row[0].get_text(strip=True)
    if len(company_row) == 2:
        location = company_row[1].get_text(strip=True).strip("-").strip(" \r").strip("\n")
    else:
        location = ""
    job_id = html['data-jobid']
    return {
    'title': title, 
    'company': company, 
    'location': location, 
    'apply_link': f"https://stackoverflow.com/jobs/{job_id}"
    }

def extract_so_jobs(last_page, url_2):
    jobs = []
    for page in range(last_page):
        print(f"Scrapping Stackoverflow page {page + 1}...")
        result = requests.get(f"{url_2}&pg={page+1}")
        soup = BeautifulSoup(result.text, "html.parser")
        results = soup.find_all("div", {"class": "-job"})
        for result in results:
            job = extract_so_job(result)
            jobs.append(job)
    return jobs

# saving

def save_to_file(jobs):
    file = open("jobs.csv", mode="w")
    writer = csv.writer(file)
    writer.writerow(["title", "company", "location", "link"])
    for job in jobs:
        writer.writerow(job.values())
    return

def get_jobs(word):
    url = f"https://kr.indeed.com/%EC%B7%A8%EC%97%85?q={word}&limit=50"
    url_2 = f"https://stackoverflow.com/jobs?q={word}&sort=i"
    last_page = extract_pages(url)
    indeed_jobs = extract_jobs(last_page, url)
    last_page = get_last_page(url_2)
    stack_jobs = extract_so_jobs(last_page, url_2)
    jobs = indeed_jobs + stack_jobs
    return jobs
