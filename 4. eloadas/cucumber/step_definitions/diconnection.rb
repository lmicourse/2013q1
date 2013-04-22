
Given /^I have disabled the network$/ do
  system('rfkill block all')
end

Given /^I have enabled the network$/ do
  system('rfkill unblock all')
end

When /^I wait (\d+) sec$/ do |sec|
  sleep(sec.to_i)
end

Then /^the error message should be (.*)$/ do |msg|
 realStatus =  File.read('status.txt')
 if not msg.strip == realStatus.strip
 	raise "Message should be '"+msg+"' but it is '"+ realStatus +"'"
 end
end


