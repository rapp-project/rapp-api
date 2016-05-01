#!/usr/bin/env python


# Copyright 2016 RAPP

# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at

    #http://www.apache.org/licenses/LICENSE-2.0

# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

# Authors: Konstantinos Panayiotou
# contact: klpanagi@gmail.com


## @file RappCloud/CloudServices/NewsExplore.py
#
#  @copyright Rapp Projecty EU 2016
#  @author Konstantinos Panayiotou, [klpanagi@gmail.com]
#


from Service import *
from RappCloud.Objects import (
    File,
    Payload
    )


class NewsExplore(Service):
  """ NewsExplore Cloud Service class """

  def __init__(self, **kwargs):
    """!
    Constructor

    @param **kwargs - Keyword arguments. Apply values to the request attributes.
      - @ref news_engine
      - @ref keywords
      - @ref exclude_titles
      - @ref region
      - @ref topic
      - @ref num_news
    """

    # Cloud Service request arguments
    # -------------------------------------------------------------
    ## The news search engine to use.
    self.news_engine = ''
    ## Desired keywords.
    self.keywords = []
    ## Reject list of previously read articles, in order to avoid duplicates.
    self.exclude_titles = []
    ## Language/Region.
    self.region = ''
    ## Main topics, i.e. sports, politics, etc.
    self.topic = ''
    ## Number of news stories.
    self.num_news = 0
    # -------------------------------------------------------------

    super(NewsExplore, self).__init__(
        svcname='news_explore',
        **kwargs
        )


  def _make_payload(self):
    """ Make request payload object """
    return Payload(
        news_engine=self.news_engine,
        keywords=self.keywords,
        exclude_titles=self.exclude_titles,
        region=self.region,
        topic=self.topic,
        num_news=self.num_news
        )


  def _make_files(self):
    """ Create array of file object(s) """
    return []
