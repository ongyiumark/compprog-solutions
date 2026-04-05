from typing import Optional
import os
import re

import requests
from bs4 import BeautifulSoup
import pandas as pd
import tqdm

from utils import Task, Contest

CONTESTS_CACHE = "contest_data/contests.csv"
CONTEST_DETAILS_CACHE = "contest_data/contest_details.csv"
ATCODER_PATH = "AtCoder"

def get_contest_codes_from_directory(directory: str) -> list[str]:
  contest_codes = []
  for dirpath, _, filenames in os.walk(directory):
    if len(filenames) == 0:
      continue
    
    base_dirname = os.path.basename(dirpath)
    contest_codes.append(base_dirname)
  
  return contest_codes

def get_atcoder_contest_details(task_url: str) -> Contest:
  response = requests.get(task_url)
  soup = BeautifulSoup(response.text, features="html.parser")

  contest_title_tag = soup.find(class_="contest-title")
  contest_name = contest_title_tag.text
  contest_code = contest_title_tag.get("href").rsplit("/", 1)[-1].upper()

  contest = Contest(
    contest_code=contest_code,
    contest_name=contest_name
  )
  table_rows = soup.find("div", class_="panel").find("tbody").find_all("tr")
  for row in table_rows:
    data = row.find_all("td")
    task_code, task_name, *_ = [d.text for d in data]
    task_link = data[0].contents[0].get("href")
    task = Task(
      task_code=task_code,
      task_name=task_name,
      task_link=task_link
    )
    contest.add_task(task)

  return contest

def cache_contests(contests: Contest, contests_df: Optional[pd.DataFrame] = None, contest_details_df: Optional[pd.DataFrame] = None):
  if contests_df is None:
    contests_df = pd.read_csv(CONTESTS_CACHE)
  if contest_details_df is None:
    contest_details_df = pd.read_csv(CONTEST_DETAILS_CACHE)
  
  cached_contests = set(contests_df["contest_code"].values)

  contest_codes = []
  contest_names = []

  task_contest_codes = []
  task_codes = []
  task_names = []
  task_links = []
  for contest in contests:
    if contest.contest_code in cached_contests:
      print(f"Using '{contest.contest_code}' cache.")
      continue
    contest_codes.append(contest.contest_code)
    contest_names.append(contest.contest_name)

    # drop contest details with this contest code
    indices_to_drop = contest_details_df[contest_details_df["contest_code"]==contest.contest_code].index
    contest_details_df.drop(indices_to_drop, inplace=True)

    for task in contest.tasks:
      task_contest_codes.append(contest.contest_code)
      task_codes.append(task.task_code)
      task_names.append(task.task_name)
      task_links.append(task.task_link)

  new_contest_df = pd.concat([
    contests_df,
    pd.DataFrame({"contest_code": contest_codes, "contest_name": contest_names})
  ])
  new_details_df = pd.concat([
    contest_details_df,
    pd.DataFrame({
      "contest_code": task_contest_codes,
      "task_code": task_codes,
      "task_name": task_names,
      "task_link": task_links
    })
  ])
  contests_df = new_contest_df
  contest_details_df = new_details_df

  contests_df.to_csv(CONTESTS_CACHE, index=False)
  contest_details_df.to_csv(CONTEST_DETAILS_CACHE, index=False)

def cache_atcoder_contests(contest_codes: list[str]):
  task_urls = [f"https://atcoder.jp/contests/{contest_code}/tasks" for contest_code in contest_codes]
  contest_df = pd.read_csv(CONTESTS_CACHE)
  cached_contests = set(contest_df["contest_code"].values)

  is_cached_list = [contest_code in cached_contests for contest_code in contest_codes]

  contests = []
  for url, is_cached in tqdm.tqdm(list(zip(task_urls, is_cached_list)), desc="Caching AtCoder"):
    if is_cached:
      print(f"Using cache for {url}.")
      continue
    
    try:
      contest = get_atcoder_contest_details(url)
      contests.append(contest)
    except:
      print(f"Failed to get {url}.")
  
  cache_contests(contests, contests_df=contest_df)


def main():
  atcoder_codes = get_contest_codes_from_directory(ATCODER_PATH)
  cache_atcoder_contests(atcoder_codes)


if __name__ == "__main__":
  main()