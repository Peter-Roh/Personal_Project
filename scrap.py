import requests
from bs4 import BeautifulSoup
import csv

URL = "https://kr.indeed.com/%EC%B7%A8%EC%97%85?q=python&limit=50"

def extract_pages():
    result = requests.get(URL)
    soup = BeautifulSoup(result.text, 'html.parser')
    pagination = soup.find("div", {"class": "pagination"})
    links = pagination.find_all("a")
    pages = []
    for page in links[:-1]:
        pages.append(int(page.string))
    max_page = pages[-1]
    return max_page

def extract_job(html):
    title = html.find("div", {"class": "title"}).find("a")["title"]
    company = html.find("span", {"class": "company"})
    if company.find("a") is not None:
        company = str(company.find("a").string)
    else:
        company = str(company.string)
    company = company.strip()
    location = html.find("span", {"class": "location"}).string
    job_id = html["data-jk"]
    return {"title": title, "company": company, "location": location, "link": f"https://kr.indeed.com/jobs?q=python&limit=50&start=200&vjk={job_id}"}

def extract_jobs(last_page):
    jobs = []
    for page in range(last_page):
        print(f"Scrapping page {page + 1}...")
        result = requests.get(URL+"&start={}".format(page*50))
        soup = BeautifulSoup(result.text, 'html.parser')
        results = soup.find_all("div", {"class": "jobsearch-SerpJobCard"})
        for item in results:
            job = extract_job(item)
            jobs.append(job)
    return jobs

def save_to_file(jobs):
    file = open("jobs.csv", mode="w")
    writer = csv.writer(file)
    writer.writerow(["title", "company", "location", "link"])
    for job in jobs:
        writer.writerow(job.values())


last_page = extract_pages()
jobs = extract_jobs(last_page)
save_to_file(jobs)
