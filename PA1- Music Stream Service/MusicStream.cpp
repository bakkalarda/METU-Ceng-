#include "MusicStream.h"

#include <iostream>

void MusicStream::addProfile(const std::string &email, const std::string &username, SubscriptionPlan plan) {
    Profile x(email, username, plan);
    profiles.insertAtTheEnd(x);
}

void MusicStream::deleteProfile(const std::string &email) {
    Node<Profile> *curr;
    Node<Profile*> *curr2;
    Node<Profile*> *curr3;
    Node<Playlist> *curr4;
    LinkedList<Profile *> x;
    LinkedList<Profile *> y;
    LinkedList<Profile *> z;
    LinkedList<Playlist> t;
    curr = profiles.getFirstNode();
    while(curr->data.getEmail() != email)
    {
    	curr = curr->next;
	}
	x = curr->data.getFollowers();
	if(x.getFirstNode() != NULL)
	{
		curr2 = x.getFirstNode();
		for(int i=0; i< x.getSize(); i++)
		{
			curr2->data->unfollowProfile(&(curr->data));
			(&(curr->data.getFollowers()))->removeNode(curr2->data);
			curr2 = curr2->next;
			
		}
	}
	y = curr->data.getFollowings();
	if(y.getFirstNode() != NULL)
	{
		curr3 = y.getFirstNode();
		for(int j=0; j< y.getSize(); j++)
		{
		    (&(curr->data))->unfollowProfile(curr3->data);
		    (&(curr3->data->getFollowers()))->removeNode(&(curr->data));
		    curr3 = curr3->next;
		}
	}
	y.removeAllNodes();
	x.removeAllNodes();
	t = curr->data.getPlaylists();
	curr4 = t.getFirstNode();
	for(int k=0; k< t.getSize(); k++)
	{
	    curr->data.deletePlaylist(curr4->data.getPlaylistId());
	    curr4 = curr4->next;
	}
	profiles.removeNode(curr);
}

void MusicStream::addArtist(const std::string &artistName) {
    Artist x(artistName);
    artists.insertAtTheEnd(x);
}

void MusicStream::addAlbum(const std::string &albumName, int artistId) {
    Node<Artist> *curr;
    Album y(albumName);
    Album *x;
    curr = artists.getFirstNode();
    while(curr->data.getArtistId() != artistId)
    {
    	curr = curr->next;
	}
	albums.insertAtTheEnd(y);
	x = &(albums.getLastNode()->data);
	curr->data.addAlbum(x);
}

void MusicStream::addSong(const std::string &songName, int songDuration, int albumId) {
   	Node<Album> *curr;
    Song y(songName, songDuration);
    Song *x;
    curr = albums.getFirstNode();
    while(curr->data.getAlbumId() != albumId)
    {
    	curr = curr->next;
	}
	songs.insertAtTheEnd(y);
	x = &(songs.getLastNode()->data);
	curr->data.addSong(x);
}

void MusicStream::followProfile(const std::string &email1, const std::string &email2) {
    Node<Profile> *curr;
    Profile *y;
    Profile * y2;
    LinkedList<Profile*> x;
    curr = profiles.getFirstNode();
    while(curr->data.getEmail() != email1)
    {
    	curr = curr->next;
	}
	Node<Profile> *curr2;
	curr2 = profiles.getFirstNode();
	while(curr2->data.getEmail() != email2)
	{
		curr2 = curr2->next;
	}
	y = &(curr2->data);
	y2 = &(curr->data);
	curr->data.followProfile(y);
	(curr2->data.getFollowers()).insertAtTheEnd(y2);
}

void MusicStream::unfollowProfile(const std::string &email1, const std::string &email2) {
    Node<Profile> *curr;
    Profile *y;
    Profile *y2;
    curr = profiles.getFirstNode();
    while(curr->data.getEmail() != email1)
    {
    	curr = curr->next;
	}
	Node<Profile> *curr2;
	curr2 = profiles.getFirstNode();
	while(curr2->data.getEmail() != email2)
	{
		curr2 = curr2->next;
	}
	y = &(curr2->data);
	y2 = &(curr->data);
	curr->data.unfollowProfile(y);
	(curr2->data.getFollowers()).removeNode(y2);
}

void MusicStream::createPlaylist(const std::string &email, const std::string &playlistName) {
    Node<Profile> *curr;
    curr = profiles.getFirstNode();
    while(curr->data.getEmail() != email)
    {
    	curr = curr->next;
	}
	curr->data.createPlaylist(playlistName);
}

void MusicStream::deletePlaylist(const std::string &email, int playlistId) {
    Node<Profile> *curr;
    curr = profiles.getFirstNode();
    while(curr->data.getEmail() != email)
    {
    	curr = curr->next;
	}
	curr->data.deletePlaylist(playlistId);
}

void MusicStream::addSongToPlaylist(const std::string &email, int songId, int playlistId) {
    Node<Profile> *curr;
    Song* y;
    curr = profiles.getFirstNode();
    while(curr->data.getEmail() != email)
    {
    	curr = curr->next;
	}
	Node<Song> *curr2;
	curr2 = songs.getFirstNode();
	while(curr2->data.getSongId() != songId)
	{
		curr2 = curr2->next;
	}
	y = &(curr2->data);
	curr->data.addSongToPlaylist(y, playlistId);
}

void MusicStream::deleteSongFromPlaylist(const std::string &email, int songId, int playlistId) {
    Node<Profile> *curr;
    Song* y;
    curr = profiles.getFirstNode();
    while(curr->data.getEmail() != email)
    {
    	curr = curr->next;
	}
	Node<Song> *curr2;
	curr2 = songs.getFirstNode();
	while(curr2->data.getSongId() != songId)
	{
		curr2 = curr2->next;
	}
	
	y = &(curr2->data);
	curr->data.deleteSongFromPlaylist(y, playlistId);
}

LinkedList<Song *> MusicStream::playPlaylist(const std::string &email, Playlist *playlist) {
    Node<Profile> *curr;
    curr = profiles.getFirstNode();
    while(curr->data.getEmail() != email)
    {
    	curr = curr->next;
	}
	if(curr->data.getPlan() == premium)
	{
		return playlist->getSongs();
	}
	else 
	{
		LinkedList<Song*> x;
		x = playlist->getSongs();
	    x.insertAsEveryKthNode(&Song::ADVERTISEMENT_SONG, 2);
	    return x;
	}
}

Playlist *MusicStream::getPlaylist(const std::string &email, int playlistId) {
    Playlist *x;
    Node<Profile> *curr;
    curr = profiles.getFirstNode();
    while(curr->data.getEmail() != email)
    {
    	curr = curr->next;
	}
	x = curr->data.getPlaylist(playlistId);
    return x;
}

LinkedList<Playlist *> MusicStream::getSharedPlaylists(const std::string &email) {
    Node<Profile> *curr;
    LinkedList<Profile *> followings;
    LinkedList<Playlist *> shareds;
    LinkedList<Playlist *> returning;
    Node<Profile*> *curr2;
    Node<Playlist*> *curr3;
    curr = profiles.getFirstNode();
    while(curr->data.getEmail() != email)
    {
    	curr = curr->next;
	}
	followings = curr->data.getFollowings();
	if(followings.getFirstNode() != NULL)
	{
	    curr2 = followings.getFirstNode();
	}
	for(int i=0; i< followings.getSize(); i++)
	{
	    shareds = curr2->data->getSharedPlaylists();
	    curr3 = shareds.getFirstNode();
        for(int j=0; j< shareds.getSize(); j++)
    	{
    	    returning.insertAtTheEnd(curr3->data);
    	    curr3 = curr3->next;
    	}
    	curr2 = curr2->next;
	}
    return returning;	    
}


void MusicStream::shufflePlaylist(const std::string &email, int playlistId, int seed) {
    Node<Profile> *curr;
    Playlist *x;
    curr = profiles.getFirstNode();
    while(curr->data.getEmail() != email)
    {
    	curr = curr->next;
	}
	x = curr->data.getPlaylist(playlistId);
	x->shuffle(seed);
}

void MusicStream::sharePlaylist(const std::string &email, int playlistId) {
    Node<Profile> *curr;
    curr = profiles.getFirstNode();
    while(curr->data.getEmail() != email)
    {
    	curr = curr->next;
	}
	Playlist *x;
	x = curr->data.getPlaylist(playlistId);
	x->setShared(true);
}

void MusicStream::unsharePlaylist(const std::string &email, int playlistId) {
    Node<Profile> *curr;
    curr = profiles.getFirstNode();
    while(curr->data.getEmail() != email)
    {
    	curr = curr->next;
	}
	Playlist *x;
	x = curr->data.getPlaylist(playlistId);
	x->setShared(false);
}

void MusicStream::subscribePremium(const std::string &email) {
    Node<Profile> *curr;
    curr = profiles.getFirstNode();
    while(curr->data.getEmail() != email)
    {
    	curr = curr->next;
	}
	curr->data.setPlan(premium);
}

void MusicStream::unsubscribePremium(const std::string &email) {
    Node<Profile> *curr;
    curr = profiles.getFirstNode();
    while(curr->data.getEmail() != email)
    {
    	curr = curr->next;
	}
	curr->data.setPlan(free_of_charge);
}

void MusicStream::print() const {
    std::cout << "# Printing the music stream ..." << std::endl;

    std::cout << "# Number of profiles is " << this->profiles.getSize() << ":" << std::endl;
    this->profiles.print();

    std::cout << "# Number of artists is " << this->artists.getSize() << ":" << std::endl;
    this->artists.print();

    std::cout << "# Number of albums is " << this->albums.getSize() << ":" << std::endl;
    this->albums.print();

    std::cout << "# Number of songs is " << this->songs.getSize() << ":" << std::endl;
    this->songs.print();

    std::cout << "# Printing is done." << std::endl;
}