# -*- mode: ruby -*-
# vi: set ft=ruby :

# Minimalistic template containing with the most important settings.

# WARNING: if you use more than one CPU on the guest
# enable hardware virtualization from your BIOS
cpus = '1'
memory = '512'

# WARNING: if you are going to run a 64 bit guest inside a 32 bit host
# you must enable hardware virtualization from your BIOS
begin
  Box = 'precise32'
  BoxUrl = 'http://files.vagrantup.com/precise32.box'
  hostname = 'cpp'
end

Vagrant.configure("2") do |config|
  config.vm.box = box
  config.vm.box_url = box_url
  config.vm.hostname = hostname
  config.vm.network :forwarded_port, guest: 4000, host: 4000
  config.vm.provider "virtualbox" do |v|
    v.customize [
      'modifyvm', :id,
      '--cpus', cpus,
      '--memory', memory,
      '--name', hostname + '_vagrant'
    ]
    if cpus.to_i > 1
      v.customize ['modifyvm', :id, '--ioapic', 'on']
    end
  end
  config.vm.provision :shell, path: 'configure'
  config.vm.provision :shell, privileged: false, inline: 'echo cd "/vagrant" >> ~/.bashrc'
end
