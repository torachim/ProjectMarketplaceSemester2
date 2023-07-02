#   python3 -m uvicorn server:app --port 8000  --reload

try:
  import handelsplatz
except ImportError as e:
  print(f"Importing the shared library 'schiffeversenken' did not work.")
  print(f"Is (a link to) the shared library 'schiffeversenken.____.so' in the same directory as this python script?")
  print(f"The import caused the following exception '{e}'")
  print(f"Exiting")
  exit(1)


from handelsplatz import Handelsplatz, Nutzer, Objekt
import os
import random
import uvicorn
from fastapi import FastAPI

app = FastAPI()
print("was")

h = Handelsplatz()