## FileSquatting Exploitation by Example

AhoyMateys => is the "signtool.exe" embedded as a resource into the QuatService.

QuatService => the vulnerable service used in this example

SquatExploit => the exploit code

SquatExploitDemo.mkv => demo of the code working

The service can be installed via powershell: 
```powershell
New-Service -Name  "QuatService" -BinaryPathName  "C:\QuatService.exe"
```

The payload.exe used in the video was taken from here: [https://gist.github.com/masthoon/6f81e466d458ff8056d76266b90d2b5e](https://gist.github.com/masthoon/6f81e466d458ff8056d76266b90d2b5e)
